// stdafx.h : 标准系统包含文件的包含文件，
// 或是经常使用但不常更改的
// 特定于项目的包含文件
//

#pragma once

#include "targetver.h"

#include <stdio.h>
#include <tchar.h>

#include <Windows.h>

#include <ctime>
#include <iostream>
#include <algorithm>
#include <string>
#include <vector>
#include <map>
#include <list>

using namespace std;

#include "include/Memory/SGIMemoryPool.hpp"
#include "include/Memory/FixedMemoryPool.hpp"

#include "include/Memory/ContainerAllocator.hpp"
#include "include/Memory/Allocator.hpp"
#include "include/Memory/MemAllocator.hpp"

using namespace async::memory;
using namespace async::thread;


#include "QPerformance.h"



//#define HAS_BOOST 1

#ifdef HAS_BOOST
#include <boost/pool/pool.hpp>
#include <boost/pool/object_pool.hpp>
#include <boost/pool/pool_alloc.hpp>
#endif