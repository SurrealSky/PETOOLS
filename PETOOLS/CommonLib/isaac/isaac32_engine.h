#ifndef ISAAC32_ENGINE_H
#define ISAAC32_ENGINE_H

#include <cstdint>
#include <limits>
#include <cstring>
#include <random>

class isaac32_engine {
public:
	typedef std::uint32_t result_type;

	static constexpr result_type default_seed = 0;
	static constexpr result_type min(void) { return std::numeric_limits<result_type>::min(); }
	static constexpr result_type max(void) { return std::numeric_limits<result_type>::max(); }
	static constexpr std::size_t randsizl(void) { return 8; }
	static constexpr std::size_t randsiz(void)  { return 1ULL << isaac32_engine::randsizl(); }

	explicit isaac32_engine(result_type value = default_seed)
		: m_randcnt(0), m_randrsl(), m_mm(), m_aa(0), m_bb(0), m_cc(0)
	{
		this->seed(value);
	}

	template<typename sseq>
	explicit isaac32_engine(sseq& s)
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
		std::memcpy(this->m_randrsl, s, sizeof(this->m_randrsl)); // sizeof(this->m_randrsl) = 1024, sizeof(s) = 8
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
			this->isaac32();
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
	std::uint32_t m_aa;
	std::uint32_t m_bb;
	std::uint32_t m_cc;

	void init(void)
	{
		std::size_t i;
		std::uint32_t a = 0x9E3779B9;
		std::uint32_t b = 0x9E3779B9;
		std::uint32_t c = 0x9E3779B9;
		std::uint32_t d = 0x9E3779B9;
		std::uint32_t e = 0x9E3779B9;
		std::uint32_t f = 0x9E3779B9;
		std::uint32_t g = 0x9E3779B9;
		std::uint32_t h = 0x9E3779B9;

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

		this->isaac32();
		this->m_randcnt = randsiz();
	}

	static void mix(std::uint32_t& a, std::uint32_t& b, std::uint32_t& c, std::uint32_t& d, std::uint32_t& e, std::uint32_t& f, std::uint32_t& g, std::uint32_t& h)
	{
		a ^= b << 11; d += a; b += c;
		b ^= c >> 2;  e += b; c += d;
		c ^= d << 8;  f += c; d += e;
		d ^= e >> 16; g += d; e += f;
		e ^= f << 10; h += e; f += g;
		f ^= g >> 4;  a += f; g += h;
		g ^= h << 8;  b += g; h += a;
		h ^= a >> 9;  c += h; a += b;
	}

	void isaac32(void)
	{
		std::uint32_t x, y;
		unsigned int i = 0;

		++this->m_cc;
		this->m_bb += this->m_cc;

		while (i<randsiz()) {
			x                  = this->m_mm[i];
			this->m_aa        ^= (this->m_aa << 13);
			this->m_aa        += this->m_mm[std::uint8_t(i + 128)];
			y                  = this->m_mm[std::uint8_t(x >> 2)] + this->m_aa + this->m_bb;
			this->m_mm[i]      = y;
			this->m_bb         = this->m_mm[std::uint8_t(y >> 10)] + x;
			this->m_randrsl[i] = this->m_bb;
			++i;

			x                  = this->m_mm[i];
			this->m_aa        ^= (this->m_aa >> 6);
			this->m_aa        += this->m_mm[std::uint8_t(i + 128)];
			y                  = this->m_mm[std::uint8_t(x >> 2)] + this->m_aa + this->m_bb;
			this->m_mm[i]      = y;
			this->m_bb         = this->m_mm[std::uint8_t(y >> 10)] + x;
			this->m_randrsl[i] = this->m_bb;
			++i;

			x                  = this->m_mm[i];
			this->m_aa        ^= (this->m_aa << 2);
			this->m_aa        += this->m_mm[std::uint8_t(i + 128)];
			y                  = this->m_mm[std::uint8_t(x >> 2)] + this->m_aa + this->m_bb;
			this->m_mm[i]      = y;
			this->m_bb         = this->m_mm[std::uint8_t(y >> 10)] + x;
			this->m_randrsl[i] = this->m_bb;
			++i;

			x                  = this->m_mm[i];
			this->m_aa        ^= (this->m_aa >> 16);
			this->m_aa        += this->m_mm[std::uint8_t(i + 128)];
			y                  = this->m_mm[std::uint8_t(x >> 2)] + this->m_aa + this->m_bb;
			this->m_mm[i]      = y;
			this->m_bb         = this->m_mm[std::uint8_t(y >> 10)] + x;
			this->m_randrsl[i] = this->m_bb;
			++i;
		}
	}

	isaac32_engine(const isaac32_engine&) = delete;
	isaac32_engine& operator=(const isaac32_engine&) = delete;
};

template<>
void isaac32_engine::seed(std::seed_seq& s)
{
	s.generate(this->m_randrsl, this->m_randrsl + randsiz());
	this->init();
}

#endif // ISAAC32_ENGINE_H
