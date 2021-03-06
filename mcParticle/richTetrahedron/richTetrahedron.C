/*---------------------------------------------------------------------------*\
                pdfFoam: General Purpose PDF Solution Algorithm
                   for Reactive Flow Simulations in OpenFOAM

 Copyright (C) 2012 Michael Wild, Heng Xiao, Patrick Jenny,
                    Institute of Fluid Dynamics, ETH Zurich
-------------------------------------------------------------------------------
License
    This file is part of pdfFoam.

    pdfFoam is free software: you can redistribute it and/or modify it
    under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 2 of the License, or
    (at your option) version 3 of the same License.

    pdfFoam is distributed in the hope that it will be useful, but WITHOUT
    ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
    FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
    for more details.

    You should have received a copy of the GNU General Public License
    along with pdfFoam.  If not, see <http://www.gnu.org/licenses/>.

\*---------------------------------------------------------------------------*/

// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //


#define CHECK_PLANE(normal, basePt)                                           \
    {                                                                         \
        n = normal;                                                           \
        n /= (Foam::mag(n) + VSMALL);                                         \
        if (((pt - basePt) & n) > SMALL)                                      \
        {                                                                     \
            return false;                                                     \
        }                                                                     \
    }

template<class Point, class PointRef>
bool Foam::richTetrahedron<Point, PointRef>::inside(const point& pt) const
{
    vector n;
    /*
    CHECK_PLANE(Sa(), b())
    CHECK_PLANE(Sb(), c())
    CHECK_PLANE(Sc(), b())
    CHECK_PLANE(Sd(), b())
    */
    {
        n = Sa();
        n /= (Foam::mag(n) + VSMALL);
        //vector d = pt - b();
        //scalar s = (pt - b()) & n;
        if (((pt - b()) & n) > SMALL)
        {
            return false;
        }
    }
    {
        n = Sb();
        n /= (Foam::mag(n) + VSMALL);
        //vector d = pt - c();
        //scalar s = (pt - c()) & n;
        if (((pt - c()) & n) > SMALL)
        {
            return false;
        }
    }
    {
        n = Sc();
        n /= (Foam::mag(n) + VSMALL);
        //vector d = pt - b();
        //scalar s = (pt - b()) & n;
        if (((pt - b()) & n) > SMALL)
        {
            return false;
        }
    }
    {
        n = Sd();
        n /= (Foam::mag(n) + VSMALL);
        //vector d = pt - b();
        //scalar s = (pt - b()) & n;
        if (((pt - b()) & n) > SMALL)
        {
            return false;
        }
    }

    return true;
}

#undef CHECK_PLANE

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //


// ************************************************************************* //
