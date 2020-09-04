#ifndef ISAAC64_ENGINE_H
#define ISAAC64_ENGINE_H

#include <cstdint>
#include <limits>
#include <cstring>
#include <random>

class isaac64_engine {
public:
	typedef std::uint64_t result_type;

	static constexpr result_type default_seed = 0;
	static constexpr result_type min(void) { return std::numeric_limits<result_type>::min(); }
	static constexpr result_type max(void) { return std::numeric_limits<result_type>::max(); }
	static constexpr std::size_t randsizl(void) { return 8; }
	static constexpr std::size_t randsiz(void)  { return 1ULL << isaac64_engine::randsizl(); }

	explicit isaac64_engine(result_type value = default_seed)
		: m_randcnt(0), m_randrsl(), m_mm(), m_aa(0), m_bb(0), m_cc(0)
	{
		this->seed(value);
	}

	template<typename sseq>
	explicit isaac64_engine(sseq& s)
		: m_randcnt(0), m_randrsl(), m_mm(), m_aa(0), m_bb(0), m_cc(0)
	{
		this->seed(s);
	}

	void seed(result_type value = default_seed)
	{
		for (std::size_t i=0; i<randsiz(); ++i) {
			this->m_randrsl[i] = value;
		}

		this->init();
	}

	void seed(result_type s[256])
	{
		std::memcpy(this->m_randrsl, s, sizeof(this->m_randrsl)); // sizeof(this->m_randrsl) = 2048, sizeof(s) = 8
		this->init();
	}

	template<typename Sseq>
	void seed(Sseq& s)
	{
		for (std::size_t i=0; i<randsiz(); ++i) {
			this->m_randrsl[i] = s();
		}
	}

	result_type operator()(void)
	{
		if (!this->m_randcnt) {
			this->isaac64();
			this->m_randcnt = randsiz() - 1;
			return this->m_randrsl[this->m_randcnt];
		}

		--this->m_randcnt;
		return this->m_randrsl[this->m_randcnt];
	}

	void discard(unsigned long long z)
	{
		while (z) {
			this->operator()();
			--z;
		}
	}

private:
	std::size_t m_randcnt;
	result_type m_randrsl[256];
	result_type m_mm[256];
	std::uint64_t m_aa;
	std::uint64_t m_bb;
	std::uint64_t m_cc;

	void init(void)
	{
		std::size_t i;
		std::uint64_t a = 0x9E3779B97F4A7C13LL;
		std::uint64_t b = 0x9E3779B97F4A7C13LL;
		std::uint64_t c = 0x9E3779B97F4A7C13LL;
		std::uint64_t d = 0x9E3779B97F4A7C13LL;
		std::uint64_t e = 0x9E3779B97F4A7C13LL;
		std::uint64_t f = 0x9E3779B97F4A7C13LL;
		std::uint64_t g = 0x9E3779B97F4A7C13LL;
		std::uint64_t h = 0x9E3779B97F4A7C13LL;

		this->m_aa = 0;
		this->m_bb = 0;
		this->m_cc = 0;

		for (i=0; i<4; ++i) {
			mix(a, b, c, d, e, f, g, h);
		}

		for (i=0; i<randsiz(); i+=8) {
			a += this->m_randrsl[i+0];
			b += this->m_randrsl[i+1];
			c += this->m_randrsl[i+2];
			d += this->m_randrsl[i+3];
			e += this->m_randrsl[i+4];
			f += this->m_randrsl[i+5];
			g += this->m_randrsl[i+6];
			h += this->m_randrsl[i+7];

			mix(a, b, c, d, e, f, g, h);

			this->m_mm[i+0] = a;
			this->m_mm[i+1] = b;
			this->m_mm[i+2] = c;
			this->m_mm[i+3] = d;
			this->m_mm[i+4] = e;
			this->m_mm[i+5] = f;
			this->m_mm[i+6] = g;
			this->m_mm[i+7] = h;
		}

		for (i=0; i<randsiz(); i+=8) {
			a += this->m_mm[i+0];
			b += this->m_mm[i+1];
			c += this->m_mm[i+2];
			d += this->m_mm[i+3];
			e += this->m_mm[i+4];
			f += this->m_mm[i+5];
			g += this->m_mm[i+6];
			h += this->m_mm[i+7];

			mix(a, b, c, d, e, f, g, h);

			this->m_mm[i+0] = a;
			this->m_mm[i+1] = b;
			this->m_mm[i+2] = c;
			this->m_mm[i+3] = d;
			this->m_mm[i+4] = e;
			this->m_mm[i+5] = f;
			this->m_mm[i+6] = g;
			this->m_mm[i+7] = h;
		}

		this->isaac64();
		this->m_randcnt = randsiz();
	}

	static void mix(std::uint64_t& a, std::uint64_t& b, std::uint64_t& c, std::uint64_t& d, std::uint64_t& e, std::uint64_t& f, std::uint64_t& g, std::uint64_t& h)
	{
		a -= e; f ^= h >> 9;  h += a;
		b -= f; g ^= a << 9;  a += b;
		c -= g; h ^= b >> 23; b += c;
		d -= h; a ^= c << 15; c += d;
		e -= a; b ^= d >> 14; d += e;
		f -= b; c ^= e << 20; e += f;
		g -= c; d ^= f >> 17; f += g;
		h -= d; e ^= g << 14; g += h;
	}


	static std::uint64_t ind(const std::uint64_t* mm, std::uint64_t x)
	{
		return *(reinterpret_cast<const uint64_t*>(reinterpret_cast<const uint8_t*>(mm) + (x & ((randsiz()-1) << 3))));
	}

	static void rngstep(std::uint64_t mix, std::uint64_t& a, std::uint64_t& b, result_type* mm, result_type*& m, result_type*& m2, result_type*& r, std::uint64_t& x, std::uint64_t& y)
	{
		x      = *m;
		a      = mix + *(m2++);
		*(m++) = y = ind(mm, x) + a + b;
		*(r++) = b = ind(mm, y >> randsizl()) + x;
	}

	void isaac64(void)
	{
		std::uint64_t x, y;
		result_type* m    = this->m_mm;
		result_type* m2   = m + (randsiz() >> 1);
		result_type* r    = this->m_randrsl;
		result_type* mend = m2;

		++this->m_cc;
		std::uint64_t a = this->m_aa;
		std::uint64_t b = this->m_bb + this->m_cc;

		while (m < mend) {
			rngstep(~(a ^ (a << 21)), a, b, this->m_mm, m, m2, r, x, y);
			rngstep(  a ^ (a >> 5),   a, b, this->m_mm, m, m2, r, x, y);
			rngstep(  a ^ (a << 12),  a, b, this->m_mm, m, m2, r, x, y);
			rngstep(  a ^ (a >> 33),  a, b, this->m_mm, m, m2, r, x, y);
		}

		m2 = this->m_mm;
		while (m2 < mend) {
			rngstep(~(a ^ (a << 21)), a, b, this->m_mm, m, m2, r, x, y);
			rngstep(  a ^ (a >> 5),   a, b, this->m_mm, m, m2, r, x, y);
			rngstep(  a ^ (a << 12),  a, b, this->m_mm, m, m2, r, x, y);
			rngstep(  a ^ (a >> 33),  a, b, this->m_mm, m, m2, r, x, y);
		}

		this->m_bb = b;
		this->m_aa = a;
	}

	isaac64_engine(const isaac64_engine&) = delete;
	isaac64_engine& operator=(const isaac64_engine&) = delete;
};

template<>
void isaac64_engine::seed(std::seed_seq& s)
{
	std::uint32_t vals[randsiz() << 1];
	s.generate(vals, vals + (randsiz() << 1));

	for (std::size_t i=0, j=0; i<randsiz()<<1; i+=2, ++j) {
		this->m_randrsl[j] = (std::uint64_t(vals[i]) << 32) | vals[i+1];
	}

	this->init();
}

#endif // ISAAC64_ENGINE_H
