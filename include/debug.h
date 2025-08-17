/*
 * debug.h
 *
 *  Created on: Nov 12, 2021
 *      Author: pjarnot
 */

#ifndef NDEBUG

#ifndef SOURCE_INCLUDE_DEBUG_H_
#define SOURCE_INCLUDE_DEBUG_H_

#include <chrono>
#include <iostream>

#define DEBUG(MESSAGE) std::cerr << "[DEB] " << __FILE__ << ":" << __FUNCTION__ << ":" << __LINE__ << ":" << MESSAGE << std::endl; std::cerr.flush();
#define WARNING(MESSAGE) std::cerr << "[WAR] " << __FILE__ << ":" << __FUNCTION__ << ":" << __LINE__ << ":" << MESSAGE << std::endl; std::cerr.flush();
#define INFO(MESSAGE) std::cerr << "[INF] " << __FILE__ << ":" << __FUNCTION__ << ":" << __LINE__ << ":" << MESSAGE << std::endl; std::cerr.flush();


#define MEASURE_TIME_BEGIN() auto t1 = std::chrono::high_resolution_clock::now();
#define MEASURE_TIME_END() auto t2 = std::chrono::high_resolution_clock::now(); DEBUG(  std::chrono::duration_cast<std::chrono::nanoseconds>(t2 - t1).count() );

#define MEASURE_TIME_BEGIN_NEXT() t1 = std::chrono::high_resolution_clock::now();
#define MEASURE_TIME_END_NEXT() t2 = std::chrono::high_resolution_clock::now(); DEBUG(  std::chrono::duration_cast<std::chrono::nanoseconds>(t2 - t1).count() );


#endif /* SOURCE_INCLUDE_DEBUG_H_ */

#else

#define DEBUG(MESSAGE)
#define WARNING(MESSAGE)
#define INFO(MESSAGE)


#define MEASURE_TIME_BEGIN()
#define MEASURE_TIME_END()

#define MEASURE_TIME_BEGIN_NEXT()
#define MEASURE_TIME_END_NEXT()

#endif /* NDEBUG_ */
