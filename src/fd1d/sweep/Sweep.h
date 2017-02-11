#ifndef FD1D_SWEEP_H
#define FD1D_SWEEP_H

/*
* PSCF - Polymer Self-Consistent Field Theory
*
* Copyright 2016, The Regents of the University of Minnesota
* Distributed under the terms of the GNU General Public License.
*/

#include <util/param/ParamComposite.h>        // base class
#include <fd1d/SystemAccess.h>                // base class
#include <fd1d/misc/HomogeneousComparison.h>  // member

#include <util/global.h>

namespace Pscf {
namespace Fd1d
{

   using namespace Util;

   /**
   * Solve a sequence of problems along a line in parameter space.
   *
   * \ingroup Pscf_Fd1d_Module
   */
   class Sweep : public ParamComposite, public SystemAccess
   {

   public:

      /**
      * Default Constructor.
      * 
      * Objects instantiated with this constructor must also call
      * the setSystem() function.
      */
      Sweep();

      /**
      * Constructor.
      * 
      * \param system parent System object.
      */
      Sweep(System& system);

      /**
      * Destructor.
      */
      ~Sweep();

      /**
      * Read ns and baseFileName parameters.
      *
      * \param in input stream
      */
      virtual void readParameters(std::istream& in);

      /**
      * Setup operation at beginning sweep.
      */
      virtual void setup(){};

      /**
      * Set system parameters.
      *
      * \param s path length coordinate, in range [0,1]
      */
      virtual void setState(double s) = 0;

      /**
      * Output information after obtaining a converged solution.
      *
      * \param stateFileName base name of output files
      * \param s value of path length parameter s
      */
      virtual void outputSolution(std::string const & stateFileName, double s);

      /**
      * Output data to a running summary.
      *
      * \param outFile  output file, open for writing
      * \param i  integer index
      * \param s  value of path length parameter s
      */
      virtual void outputSummary(std::ostream& outFile, int i, double s);

      /**
      * Iterate to solution.
      */
      virtual void solve();

   protected:

      /// Number of steps. 
      int ns_;

      /// Mode for comparison to homogeneous system (none -> -1)
      int homogeneousMode_;

      /// Base name for output files
      std::string baseFileName_;

   private:

      /// Algorithm for comparing to a homogeneous system
      HomogeneousComparison comparison_;

   };

} // namespace Fd1d
} // namespace Pscf
#endif
