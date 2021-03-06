#ifndef BOOST_GEOMETRY_PROJECTIONS_IGH_HPP
#define BOOST_GEOMETRY_PROJECTIONS_IGH_HPP

// Boost.Geometry - extensions-gis-projections (based on PROJ4)
// This file is automatically generated. DO NOT EDIT.

// Copyright (c) 2008-2015 Barend Gehrels, Amsterdam, the Netherlands.

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

// This file is converted from PROJ4, http://trac.osgeo.org/proj
// PROJ4 is originally written by Gerald Evenden (then of the USGS)
// PROJ4 is maintained by Frank Warmerdam
// PROJ4 is converted to Boost.Geometry by Barend Gehrels

// Last updated version of proj: 4.9.1

// Original copyright notice:

// Permission is hereby granted, free of charge, to any person obtaining a
// copy of this software and associated documentation files (the "Software"),
// to deal in the Software without restriction, including without limitation
// the rights to use, copy, modify, merge, publish, distribute, sublicense,
// and/or sell copies of the Software, and to permit persons to whom the
// Software is furnished to do so, subject to the following conditions:

// The above copyright notice and this permission notice shall be included
// in all copies or substantial portions of the Software.

// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
// OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
// THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
// FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
// DEALINGS IN THE SOFTWARE.

#include <boost/geometry/util/math.hpp>
#include <boost/shared_ptr.hpp>

#include <boost/geometry/extensions/gis/projections/impl/base_static.hpp>
#include <boost/geometry/extensions/gis/projections/impl/base_dynamic.hpp>
#include <boost/geometry/extensions/gis/projections/impl/projects.hpp>
#include <boost/geometry/extensions/gis/projections/impl/factory_entry.hpp>
#include <boost/geometry/extensions/gis/projections/proj/gn_sinu.hpp>
#include <boost/geometry/extensions/gis/projections/proj/moll.hpp>

namespace boost { namespace geometry { namespace projections
{
    #ifndef DOXYGEN_NO_DETAIL
    namespace detail { namespace igh
    {

            template <typename Geographic, typename Cartesian>
            struct par_igh
            {
                boost::shared_ptr<projection<Geographic, Cartesian> > pj[12];
                double dy0;
            };

            static const double d4044118 = (40 + 44/60. + 11.8/3600.) * geometry::math::d2r<double>(); // 40d 44' 11.8" [degrees]

            static const double d10  =  10 * geometry::math::d2r<double>();
            static const double d20  =  20 * geometry::math::d2r<double>();
            static const double d30  =  30 * geometry::math::d2r<double>();
            static const double d40  =  40 * geometry::math::d2r<double>();
            static const double d50  =  50 * geometry::math::d2r<double>();
            static const double d60  =  60 * geometry::math::d2r<double>();
            static const double d80  =  80 * geometry::math::d2r<double>();
            static const double d90  =  90 * geometry::math::d2r<double>();
            static const double d100 = 100 * geometry::math::d2r<double>();
            static const double d140 = 140 * geometry::math::d2r<double>();
            static const double d160 = 160 * geometry::math::d2r<double>();
            static const double d180 = 180 * geometry::math::d2r<double>();

            static const double EPSLN = 1.e-10; // allow a little 'slack' on zone edge positions

            // Converted from #define SETUP(n, proj, x_0, y_0, lon_0)
            template <template <typename, typename, typename> class Entry, typename Parameters, typename Geographic, typename Cartesian>
            inline void do_setup(int n, Parameters const& par, par_igh<Geographic, Cartesian>& proj_parm, double x_0, double y_0, double lon_0)
            {
                Entry<Geographic, Cartesian, Parameters> entry;
                proj_parm.pj[n-1].reset(entry.create_new(par));
                proj_parm.pj[n-1]->mutable_params().x0 = x_0;
                proj_parm.pj[n-1]->mutable_params().y0 = y_0;
                proj_parm.pj[n-1]->mutable_params().lam0 = lon_0;
            }

            // template class, using CRTP to implement forward/inverse
            template <typename Geographic, typename Cartesian, typename Parameters>
            struct base_igh_spheroid : public base_t_fi<base_igh_spheroid<Geographic, Cartesian, Parameters>,
                     Geographic, Cartesian, Parameters>
            {

                 typedef double geographic_type;
                 typedef double cartesian_type;

                par_igh<Geographic, Cartesian> m_proj_parm;

                inline base_igh_spheroid(const Parameters& par)
                    : base_t_fi<base_igh_spheroid<Geographic, Cartesian, Parameters>,
                     Geographic, Cartesian, Parameters>(*this, par) {}

                // FORWARD(s_forward)  spheroid
                // Project coordinates from geographic (lon, lat) to cartesian (x, y)
                inline void fwd(geographic_type& lp_lon, geographic_type& lp_lat, cartesian_type& xy_x, cartesian_type& xy_y) const
                {
                        int z;
                        if (lp_lat >=  d4044118) {          // 1|2
                          z = (lp_lon <= -d40 ? 1: 2);
                        }
                        else if (lp_lat >=  0) {            // 3|4
                          z = (lp_lon <= -d40 ? 3: 4);
                        }
                        else if (lp_lat >= -d4044118) {     // 5|6|7|8
                               if (lp_lon <= -d100) z =  5; // 5
                          else if (lp_lon <=  -d20) z =  6; // 6
                          else if (lp_lon <=   d80) z =  7; // 7
                          else z = 8;                       // 8
                        }
                        else {                              // 9|10|11|12
                               if (lp_lon <= -d100) z =  9; // 9
                          else if (lp_lon <=  -d20) z = 10; // 10
                          else if (lp_lon <=   d80) z = 11; // 11
                          else z = 12;                      // 12
                        }

                        lp_lon -= this->m_proj_parm.pj[z-1]->params().lam0;
                        this->m_proj_parm.pj[z-1]->fwd(lp_lon, lp_lat, xy_x, xy_y);
                        xy_x += this->m_proj_parm.pj[z-1]->params().x0;
                        xy_y += this->m_proj_parm.pj[z-1]->params().y0;
                }

                // INVERSE(s_inverse)  spheroid
                // Project coordinates from cartesian (x, y) to geographic (lon, lat)
                inline void inv(cartesian_type& xy_x, cartesian_type& xy_y, geographic_type& lp_lon, geographic_type& lp_lat) const
                {
                        const double y90 = this->m_proj_parm.dy0 + sqrt(2.0); // lt=90 corresponds to y=y0+sqrt(2.0)

                        int z = 0;
                        if (xy_y > y90+EPSLN || xy_y < -y90+EPSLN) // 0
                          z = 0;
                        else if (xy_y >=  d4044118)       // 1|2
                          z = (xy_x <= -d40? 1: 2);
                        else if (xy_y >=  0)              // 3|4
                          z = (xy_x <= -d40? 3: 4);
                        else if (xy_y >= -d4044118) {     // 5|6|7|8
                               if (xy_x <= -d100) z =  5; // 5
                          else if (xy_x <=  -d20) z =  6; // 6
                          else if (xy_x <=   d80) z =  7; // 7
                          else z = 8;                     // 8
                        }
                        else {                            // 9|10|11|12
                               if (xy_x <= -d100) z =  9; // 9
                          else if (xy_x <=  -d20) z = 10; // 10
                          else if (xy_x <=   d80) z = 11; // 11
                          else z = 12;                    // 12
                        }

                        if (z)
                        {
                          int ok = 0;

                          xy_x -= this->m_proj_parm.pj[z-1]->params().x0;
                          xy_y -= this->m_proj_parm.pj[z-1]->params().y0;
                          this->m_proj_parm.pj[z-1]->inv(xy_x, xy_y, lp_lon, lp_lat);
                          lp_lon += this->m_proj_parm.pj[z-1]->params().lam0;

                          switch (z) {
                            case  1: ok = (lp_lon >= -d180-EPSLN && lp_lon <=  -d40+EPSLN) ||
                                         ((lp_lon >=  -d40-EPSLN && lp_lon <=  -d10+EPSLN) &&
                                          (lp_lat >=   d60-EPSLN && lp_lat <=   d90+EPSLN)); break;
                            case  2: ok = (lp_lon >=  -d40-EPSLN && lp_lon <=  d180+EPSLN) ||
                                         ((lp_lon >= -d180-EPSLN && lp_lon <= -d160+EPSLN) &&
                                          (lp_lat >=   d50-EPSLN && lp_lat <=   d90+EPSLN)) ||
                                         ((lp_lon >=  -d50-EPSLN && lp_lon <=  -d40+EPSLN) &&
                                          (lp_lat >=   d60-EPSLN && lp_lat <=   d90+EPSLN)); break;
                            case  3: ok = (lp_lon >= -d180-EPSLN && lp_lon <=  -d40+EPSLN); break;
                            case  4: ok = (lp_lon >=  -d40-EPSLN && lp_lon <=  d180+EPSLN); break;
                            case  5: ok = (lp_lon >= -d180-EPSLN && lp_lon <= -d100+EPSLN); break;
                            case  6: ok = (lp_lon >= -d100-EPSLN && lp_lon <=  -d20+EPSLN); break;
                            case  7: ok = (lp_lon >=  -d20-EPSLN && lp_lon <=   d80+EPSLN); break;
                            case  8: ok = (lp_lon >=   d80-EPSLN && lp_lon <=  d180+EPSLN); break;
                            case  9: ok = (lp_lon >= -d180-EPSLN && lp_lon <= -d100+EPSLN); break;
                            case 10: ok = (lp_lon >= -d100-EPSLN && lp_lon <=  -d20+EPSLN); break;
                            case 11: ok = (lp_lon >=  -d20-EPSLN && lp_lon <=   d80+EPSLN); break;
                            case 12: ok = (lp_lon >=   d80-EPSLN && lp_lon <=  d180+EPSLN); break;
                          }

                          z = (!ok? 0: z); // projectable?
                        }
                     // if (!z) pj_errno = -15; // invalid x or y
                        if (!z) lp_lon = HUGE_VAL;
                        if (!z) lp_lat = HUGE_VAL;
                }

                static inline std::string get_name()
                {
                    return "igh_spheroid";
                }

            };

            // Interrupted Goode Homolosine
            template <typename Geographic, typename Cartesian, typename Parameters>
            void setup_igh(Parameters& par, par_igh<Geographic, Cartesian>& proj_parm)
            {
            /*
              Zones:

                -180            -40                       180
                  +--------------+-------------------------+    Zones 1,2,9,10,11 & 12:
                  |1             |2                        |      Mollweide projection
                  |              |                         |
                  +--------------+-------------------------+    Zones 3,4,5,6,7 & 8:
                  |3             |4                        |      Sinusoidal projection
                  |              |                         |
                0 +-------+------+-+-----------+-----------+
                  |5      |6       |7          |8          |
                  |       |        |           |           |
                  +-------+--------+-----------+-----------+
                  |9      |10      |11         |12         |
                  |       |        |           |           |
                  +-------+--------+-----------+-----------+
                -180    -100      -20         80          180
            */


                    double lp_lam = 0, lp_phi = d4044118;
                    double xy1_x, xy1_y;
                    double xy3_x, xy3_y;

                    // sinusoidal zones
                    do_setup<sinu_entry>(3, par, proj_parm, -d100, 0, -d100);
                    do_setup<sinu_entry>(4, par, proj_parm,   d30, 0,   d30);
                    do_setup<sinu_entry>(5, par, proj_parm, -d160, 0, -d160);
                    do_setup<sinu_entry>(6, par, proj_parm,  -d60, 0,  -d60);
                    do_setup<sinu_entry>(7, par, proj_parm,   d20, 0,   d20);
                    do_setup<sinu_entry>(8, par, proj_parm,  d140, 0,  d140);

                    // mollweide zones
                    do_setup<moll_entry>(1, par, proj_parm, -d100, 0, -d100);

                    // y0 ?
                     proj_parm.pj[0]->fwd(lp_lam, lp_phi, xy1_x, xy1_y); // zone 1
                     proj_parm.pj[2]->fwd(lp_lam, lp_phi, xy3_x, xy3_y); // zone 3
                    // y0 + xy1_y = xy3_y for lt = 40d44'11.8"
                    proj_parm.dy0 = xy3_y - xy1_y;

                    proj_parm.pj[0]->mutable_params().y0 = proj_parm.dy0;

                    // mollweide zones (cont'd)
                    do_setup<moll_entry>( 2, par, proj_parm,   d30,  proj_parm.dy0,   d30);
                    do_setup<moll_entry>( 9, par, proj_parm, -d160, -proj_parm.dy0, -d160);
                    do_setup<moll_entry>(10, par, proj_parm,  -d60, -proj_parm.dy0,  -d60);
                    do_setup<moll_entry>(11, par, proj_parm,   d20, -proj_parm.dy0,   d20);
                    do_setup<moll_entry>(12, par, proj_parm,  d140, -proj_parm.dy0,  d140);

                    par.es = 0.;
            }

        }} // namespace detail::igh
    #endif // doxygen

    /*!
        \brief Interrupted Goode Homolosine projection
        \ingroup projections
        \tparam Geographic latlong point type
        \tparam Cartesian xy point type
        \tparam Parameters parameter type
        \par Projection characteristics
         - Pseudocylindrical
         - Spheroid
        \par Example
        \image html ex_igh.gif
    */
    template <typename Geographic, typename Cartesian, typename Parameters = parameters>
    struct igh_spheroid : public detail::igh::base_igh_spheroid<Geographic, Cartesian, Parameters>
    {
        inline igh_spheroid(const Parameters& par) : detail::igh::base_igh_spheroid<Geographic, Cartesian, Parameters>(par)
        {
            detail::igh::setup_igh(this->m_par, this->m_proj_parm);
        }
    };

    #ifndef DOXYGEN_NO_DETAIL
    namespace detail
    {

        // Factory entry(s)
        template <typename Geographic, typename Cartesian, typename Parameters>
        class igh_entry : public detail::factory_entry<Geographic, Cartesian, Parameters>
        {
            public :
                virtual projection<Geographic, Cartesian>* create_new(const Parameters& par) const
                {
                    return new base_v_fi<igh_spheroid<Geographic, Cartesian, Parameters>, Geographic, Cartesian, Parameters>(par);
                }
        };

        template <typename Geographic, typename Cartesian, typename Parameters>
        inline void igh_init(detail::base_factory<Geographic, Cartesian, Parameters>& factory)
        {
            factory.add_to_factory("igh", new igh_entry<Geographic, Cartesian, Parameters>);
        }

    } // namespace detail
    #endif // doxygen

}}} // namespace boost::geometry::projections

#endif // BOOST_GEOMETRY_PROJECTIONS_IGH_HPP

