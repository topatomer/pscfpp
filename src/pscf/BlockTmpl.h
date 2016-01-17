#ifndef PSCF_BLOCK_TMPL_H
#define PSCF_BLOCK_TMPL_H

/*
* PFTS - Polymer Field Theory Simulator
*
* Copyright 2013, David Morse (morse012@.umn.edu)
* Distributed under the terms of the GNU General Public License.
*/

#include <pscf/BlockDescriptor.h>   // base class
#include <util/containers/Pair.h>   // member template

#include <cmath>

namespace Pscf
{ 

   class TP;
   using namespace Util;

   /**
   * Class template for a block in a block copolymer.
   */
   template <class TP>
   class BlockTmpl : public BlockDescriptor
   {

   public:

      // Modified diffusion equation propagator for one block.
      typedef TP Propagator;

      // Monomer concentration field.
      typedef typename TP::CField CField;
 
      // Chemical potential field.
      typedef typename TP::WField WField;

      /**
      * Constructor.
      */
      BlockTmpl();
 
      /**
      * Destructor.
      */
      virtual ~BlockTmpl();

      /**
      * Read parameters and initialize.
      *
      * \param in input parameter stream
      */
      virtual void readParameters(std::istream& in);

      /**
      * Get a Propagator for a specified direction.
      *
      * For a block with v0 = vertexId(0) and v1 = vertexId(1),
      * propagator(0) propagates from vertex v0 to v1, while
      * propagator(1) propagates from vertex v1 to v0.
      *
      * \param directionId integer index for direction (0 or 1)
      */
      TP& propagator(int directionId);
   
      /**
      * Get the associated monomer concentration field.
      *
      * \param blockId integer index of associated block
      */
      typename TP::CField& cField();
   
   private:

      /// Propagators (one for each direction).
      Pair<Propagator> propagators_;

      /// Monomer concentration field.
      CField cField_;

   };

   /*
   * Get a Propagator indexed by direction.
   */
   template <class TP>
   inline 
   TP& BlockTmpl<TP>::propagator(int directionId)
   {  return propagators_[directionId]; }

   /*
   * Get the monomer concentration field.
   */
   template <class TP>
   inline
   typename TP::CField& BlockTmpl<TP>::cField()
   {  return cField_; }

   // Non-inline functions

   /*
   * Constructor.
   */
   template <class TP>
   BlockTmpl<TP>::BlockTmpl()
    : propagators_(),
      cField_()
   {  setClassName("BlockTmpl"); }

   /*
   * Destructor.
   */
   template <class TP>
   BlockTmpl<TP>::~BlockTmpl()
   {}

   template <class TP>
   void BlockTmpl<TP>::readParameters(std::istream& in)
   {
      // Read topological description
      BlockDescriptor::readParameters(in);

      // Create intra-block associations
      propagator(0).setBlock(*this, 0);
      propagator(0).setPartner(propagator(1));
      propagator(1).setBlock(*this, 1);
      propagator(1).setPartner(propagator(0));
   }
 
}
#endif