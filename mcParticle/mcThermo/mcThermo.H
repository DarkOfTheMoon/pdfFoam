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
    Foam::mcThermo

Description
    Thermo class based on MC particles

Note
    The constructor does @b not create the particle cloud, because
    mcParticleCloud requires a turbulence model, but the compressible
    turbulence models also required mcThermo to be passed in their constructor.
    To break this dependency loop, it is the users responsibility to call
    mcThermo::createCloud() after creating the turbulence model.

SourceFiles
    mcThermo.C

Author
    Michael Wild

\*---------------------------------------------------------------------------*/

#ifndef mcThermo_H
#define mcThermo_H

#include "basicThermo.H"
#include "mcParticleCloud.H"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace Foam
{

/*---------------------------------------------------------------------------*\
                        Class mcThermo Declaration
\*---------------------------------------------------------------------------*/

class mcThermo
:
    public basicThermo
{
    // Private data

        //- The mesh
        const fvMesh& mesh_;

        //- Particle cloud
        autoPtr<mcParticleCloud> cloudP_;

        //- Density field
        volScalarField rho_;

        //- Viscosity
        dimensionedScalar nu_;

    // Private member functions

        //- Calculate the thermo variables
        void calculate();

        //- Construct as copy (not implemented)
        mcThermo(const mcThermo&);


public:

    //- Runtime type information
    TypeName("mcThermo");


    // Constructors

        //- Construct from mesh
        mcThermo(const fvMesh& mesh);


    //- Destructor
    virtual ~mcThermo();


    // Member functions

        //- Create the particle cloud
        void createCloud();

        //- Evolve the cloud
        // @returns The maximum residual
        scalar evolve();

        //- Update properties
        virtual void correct();

        // Fields derived from thermodynamic state variables

            //- Density [kg/m^3]
            virtual tmp<volScalarField> rho() const;

            //- Return non-const access to the local density field [kg/m^3]
            virtual volScalarField& rho();
};


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace Foam

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif

// ************************************************************************* //
