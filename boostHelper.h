/*
 * boostHelper.h
 *
 *  Created on: Oct 1, 2013
 *      Author: nut
 */

#ifndef BOOSTHELPER_H_
#define BOOSTHELPER_H_

#include <boost/geometry.hpp>
#include <boost/geometry/geometries/point.hpp>
#include <boost/geometry/geometries/box.hpp>
#include <boost/geometry/geometries/polygon.hpp>
#include <boost/geometry/geometries/geometries.hpp>
#include <boost/geometry/index/rtree.hpp>
#include <boost/geometry/geometries/point_xy.hpp>
#include <boost/foreach.hpp>
#include <boost/geometry/geometries/adapted/boost_tuple.hpp>

namespace bg = boost::geometry;
namespace bgi = boost::geometry::index;
using bg::dsv;
using bg::get;
typedef bg::model::point<float, 2, bg::cs::cartesian> point;
typedef bg::model::box<point> box;
typedef bg::model::polygon<point, false, false> polygon; // ccw, open polygon
typedef bg::model::linestring<point> linestring_2d;
typedef boost::tuple<double, double> tPoint;
typedef bg::model::referring_segment<tPoint> segment;
typedef boost::geometry::model::polygon<tPoint> tPolygon;

BOOST_GEOMETRY_REGISTER_BOOST_TUPLE_CS(cs::cartesian)



#endif /* BOOSTHELPER_H_ */
