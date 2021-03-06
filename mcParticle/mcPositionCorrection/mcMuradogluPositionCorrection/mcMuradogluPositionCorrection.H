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

Class
    Foam::mcMuradogluPositionCorrection

Description
    Position correction as described by Muradoglu et al.

    This implements an elaborate position/density correction scheme developed
    by Muradoglu et al. @cite muradoglu:2001.

Note
    The algorithm described in section 4.2, p. 854 contains typos in the
    coefficients and a corrigendum has been published. The coefficients derived
    in the appendix appear to be correct.

SourceFiles
    mcMuradogluPositionCorrection.C

Author
    Michael Wild

SeeAlso
    http://dx.doi.org/10.1006/jcph.2001.6861

\*---------------------------------------------------------------------------*/

#ifndef mcMuradogluPositionCorrection_H
#define mcMuradogluPositionCorrection_H

#include "mcEllipticRelaxationPositionCorrection.H"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace Foam
{

class mcParticleCloud;
template<class> class interpolation;

/*---------------------------------------------------------------------------*\
                Class mcMuradogluPositionCorrection Declaration
\*---------------------------------------------------------------------------*/

class mcMuradogluPositionCorrection :
    public mcEllipticRelaxationPositionCorrection
{
    // Private Data

        //- Integrated density correction potential
        volScalarField phi_;
        //- Gradient of the integrated density correction potential
        volVectorField gradPhi_;
        //- Interpolator for the integrated density correction potential
        autoPtr<interpolation<vector> > gradPhiInterp_;

    // Private Member Functions

        // Disallow default bitwise copy construct and assignment
        mcMuradogluPositionCorrection(const mcMuradogluPositionCorrection&);
        void operator=(const mcMuradogluPositionCorrection&);

public:

    //- Runtime type information
    TypeName("mcMuradogluPositionCorrection");

    // Constructors

        //- Construct from components
        mcMuradogluPositionCorrection
        (
            mcParticleCloud& cloud,
            const objectRegistry& db,
            const word& subDictName
        );


    // Member Functions

        //- Update/prepare internal data
        virtual void updateInternals();

        //- Apply the position correction
        virtual void correct(mcParticle& p);

};

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace Foam

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif

// ************************************************************************* //
