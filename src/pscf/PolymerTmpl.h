#ifndef PSCF_POLYMER_TMPL_H
#define PSCF_POLYMER_TMPL_H

/*
* PFTS - Polymer Field Theory Simulator
*
* Copyright 2013, David Morse (morse012@.umn.edu)
* Distributed under the terms of the GNU General Public License.
*/

#include <pscf/Species.h>                // base class
#include <util/param/ParamComposite.h>   // base class

#include <pscf/Monomer.h>                // member template argument
#include <pscf/Vertex.h>                 // member template argument
#include <util/containers/Pair.h>        // member template
#include <util/containers/DArray.h>      // member template
#include <util/containers/DMatrix.h>

#include <cmath>

namespace Pscf
{ 

   class Block;
   using namespace Util;

   /**
   * Structure descriptor for an acyclic block polymer.
   */
   template <class Block>
   class PolymerTmpl : public Species, public ParamComposite
   {

   public:

      // Modified diffusion equation propagator for one block.
      typedef typename Block::Propagator Propagator;

      // Monomer concentration field.
      typedef typename Propagator::CField CField;
 
      // Chemical potential field.
      typedef typename Propagator::WField WField;

      /**
      * Constructor.
      */
      PolymerTmpl();
 
      /**
      * Destructor.
      */
      ~PolymerTmpl();

      /**
      * Read and initialize.
      *
      * \param in input parameter stream
      */
      virtual void readParameters(std::istream& in);

      /**
      * Compute solution to modified diffusion equation.
      */ 
      virtual void compute(const DArray<WField>& wFields);
 
      /**
      * Number of blocks.
      */
      int nBlock() const; 

      /**
      * Number of vertices (junctions and chain ends).
      */
      int nVertex() const;

      /**
      * Number of propagators (twice nBlock).
      */
      int nPropagator() const;  //

      /**
      * Total length of all blocks = volume / reference volume.
      */
      double length() const;

      /**
      * Get a specified Block.
      * 
      * \param id block index
      */
      const Block& block(int id) const;

      /**
      * Get a specified Vertex.
      * 
      * \param id vertex index
      */
      const Vertex& vertex(int id) const;

      /**
      * Get the monomer concentration field for a specific block.
      *
      * \param blockId integer index of associated block
      */
      CField& blockCField(int blockId);
   
      /**
      * Get propagator for a specific block and direction.
      *
      * Suppose p is a PolymerTmpl, and b = p.block(i) is a block 
      * terminating at vertices with indices v0 = b.vertexId(0) and 
      * v1 = b.vertexId(1), then p.propagator(i, 0) is a propagator 
      * that from v0 to v1, while p.propagator(i, 1) propagates
      * from v1 to v0.
      *
      * \param blockId integer index of associated block
      * \param directionId integer index for direction (0 or 1)
      */
      Propagator& propagator(int blockId, int directionId);
   
      /**
      * Get propagator indexed in order of computation.
      *
      * \param id integer index, in order of computation plan
      */
      Propagator& propagator(int id);

   protected:

      /**
      * Propagator identifier, indexed by order of computation.
      *
      * An array of propagator ids ordered in the order in which 
      * they should be computed, so that the intitial condition 
      * for each link is provided by the solution of links that 
      * have been computed previously.
      */
      const Pair<int>& propagatorId(int i) const;

      virtual void makePlan();

   private:

      /// Array of Block objects in this polymer.
      DArray<Block> blocks_;

      /// Array of Vertex objects in this polymer.
      DArray<Vertex> vertices_;

      /// Propagator ids, indexed in order of computation.
      DArray< Pair<int> > propagatorIds_;

      /// Number of blocks in this polymer
      int nBlock_;

      /// Number of vertices (ends or junctions) in this polymer
      int nVertex_;

      /// Number of propagators (two per block).
      int nPropagator_;

      /// Total length of all blocks (in units of reference length).
      double length_;

   };

   /*
   * Number of vertices (ends and/or junctions)
   */
   template <class Block>
   inline int PolymerTmpl<Block>::nVertex() const
   {  return nVertex_; }

   /*
   * Number of blocks.
   */
   template <class Block>
   inline int PolymerTmpl<Block>::nBlock() const
   {  return nBlock_; }

   /*
   * Number of propagators.
   */
   template <class Block>
   inline int PolymerTmpl<Block>::nPropagator() const
   {  return nPropagator_; }

   /*
   * Total length of all blocks = volume / reference volume
   */
   template <class Block>
   inline double PolymerTmpl<Block>::length() const
   {  return length_; }

   /*
   * Get a specified Vertex.
   */
   template <class Block>
   inline 
   const Vertex& PolymerTmpl<Block>::vertex(int id) const
   {  return vertices_[id]; }

   /*
   * Get a specified Block.
   */
   template <class Block>
   inline const Block& PolymerTmpl<Block>::block(int id) const
   {  return blocks_[id]; }

   /*
   * Get a propagator id, indexed in order of computation.
   */
   template <class Block>
   inline 
   const Pair<int>& PolymerTmpl<Block>::propagatorId(int id) const
   {
      UTIL_CHECK(id >= 0);  
      UTIL_CHECK(id < nPropagator_);  
      return propagatorIds_[id]; 
   }

   /*
   * Get a propagator indexed by block and direction.
   */
   template <class Block>
   inline 
   TProp& PolymerTmpl<Block>::propagator(int blockId, int directionId)
   {  return blocks_(blockId).propagator(directionId); }

   /*
   * Get a propagator indexed in order of computation.
   */
   template <class Block>
   inline TProp& PolymerTmpl<Block>::propagator(int id)
   {
      Pair<int> propId = propagatorId(id);
      return propagators_(propId[0], propId[1]); 
   }

   /*
   * Get a block monomer concentration.
   */
   template <class Block>
   inline
   typename PolymerTmpl<Block>::CField& 
   PolymerTmpl<Block>::blockCField(int blockId)
   {  return blockCFields_[blockId]; }

   
   // Non-inline functions

   /*
   * Constructor.
   */
   template <class Block>
   PolymerTmpl<Block>::PolymerDescriptor()
    : blocks_(),
      vertices_(),
      propagatorIds_(),
      nBlock_(0),
      nVertex_(0),
      nPropagator_(0),
      length_(0.0)
   {
      setClassName("PolymerDescriptor");
   }

   /*
   * Destructor.
   */
   template <class Block>
   PolymerTmpl<Block>::~PolymerDescriptor()
   {}

   template <class Block>
   void PolymerTmpl<Block>::readParameters(std::istream& in)
   {
      read<int>(in, "nBlock", nBlock_);
      read<int>(in, "nVertex", nVertex_);

      // Allocate all arrays
      blocks_.allocate(nBlock_);
      vertices_.allocate(nVertex_);
      propagatorIds_.allocate(2*nBlock_);

      readDArray<Block>(in, "blocks", blocks_, nBlock_);

      // Set vertex indices
      for (int vertexId = 0; vertexId < nVertex_; ++vertexId) {
         vertices_[vertexId].setId(vertexId);
      }

      // Add blocks to vertices
      int vertexId0, vertexId1;
      Block* blockPtr;
      for (int blockId = 0; blockId < nBlock_; ++blockId) {
          blockPtr = &(blocks_[blockId]);
          vertexId0 = blockPtr->vertexId(0);
          vertexId1 = blockPtr->vertexId(1);
          vertices_[vertexId0].addBlock(*blockPtr);
          vertices_[vertexId1].addBlock(*blockPtr);
      }

      makePlan();

      // Compute molecular length / volume
      length_ = 0.0;
      for (int blockId = 0; blockId < nBlock_; ++blockId) {
         length_ += blocks_[blockId].length();
      }

      // Read ensemble and phi or mu
      ensemble_ = Species::Closed;
      readOptional<Species::Ensemble>(in, "ensemble", ensemble_);
      if (ensemble_ == Species::Closed) {
         read(in, "phi", phi_);
      } else {
         read(in, "mu", mu_);
      }

      blockCFields_.allocate(nBlock());
      propagators_.allocate(nBlock(), 2);

      // Associate propagators with blocks and directions
      Propagator* propagatorPtr = 0;
      int blockId, directionId;
      for (blockId = 0; blockId < nBlock(); ++blockId) {
         for (directionId = 0; directionId < 2; ++directionId) {
            propagatorPtr = &propagator(blockId, directionId);
            propagatorPtr->setBlock(block(blockId), directionId);
         }
      }
      
      // Set sources and partners for all propagators
      Vertex const * vertexPtr = 0;
      Propagator const * sourcePtr = 0;
      Pair<int> propagatorId;
      int vertexId, i;
      for (blockId = 0; blockId < nBlock(); ++blockId) {
         // Add sources
         for (directionId = 0; directionId < 2; ++directionId) {
            vertexId = block(blockId).vertexId(directionId);
            vertexPtr = &vertex(vertexId);
            propagatorPtr = &propagator(blockId, directionId);
            for (i = 0; i < vertexPtr->size(); ++i) {
               propagatorId = vertexPtr->inPropagatorId(i);
               if (propagatorId[0] == blockId) {
                  UTIL_CHECK(propagatorId[1] != directionId);
               } else {
                  sourcePtr = & propagator(propagatorId[0], propagatorId[1]);
                  propagatorPtr->addSource(*sourcePtr);
               }
            }
         }

         // Set partners
         propagator(blockId, 0).setPartner(propagator(blockId, 1));
         propagator(blockId, 1).setPartner(propagator(blockId, 0));
      }
   }

   template <class Block>
   void PolymerTmpl<Block>::makePlan()
   {
      if (nPropagator_ != 0) {
         UTIL_THROW("nPropagator !=0 on entry");
      }

      // Allocate and initialize isFinished matrix
      DMatrix<bool> isFinished;
      isFinished.allocate(nBlock_, 2);
      for (int iBlock = 0; iBlock < nBlock_; ++iBlock) {
         for (int iDirection = 0; iDirection < 2; ++iDirection) {
            isFinished(iBlock, iDirection) = false;
         }
      }

      Pair<int> propagatorId;
      Vertex* inVertexPtr = 0;
      int inVertexId = -1;
      bool isReady;
      while (nPropagator_ < nBlock_*2) {
         for (int iBlock = 0; iBlock < nBlock_; ++iBlock) {
            for (int iDirection = 0; iDirection < 2; ++iDirection) {
               if (isFinished(iBlock, iDirection) == false) {
                  inVertexId = blocks_[iBlock].vertexId(iDirection);
                  inVertexPtr = &vertices_[inVertexId];
                  isReady = true;
                  for (int j = 0; j < inVertexPtr->size(); ++j) {
                     propagatorId = inVertexPtr->inPropagatorId(j);
                     if (propagatorId[0] != iBlock) {
                        if (!isFinished(propagatorId[0], propagatorId[1])) {
                           isReady = false;
                           break;
                        }
                     }
                  }
                  if (isReady) {
                     propagatorIds_[nPropagator_][0] = iBlock;
                     propagatorIds_[nPropagator_][1] = iDirection;
                     isFinished(iBlock, iDirection) = true;
                     ++nPropagator_;
                  }
               }
            }
         }
      }

   }

   /*
   * Compute solution to MDE and concentrations.
   */ 
   template <class Block>
   void PolymerTmpl<Block>::compute(const DArray<WField>& wFields)
   {

      // Clear all propagators
      for (int j = 0; j < nPropagator(); ++j) {
         propagator(j).setIsSolved(false);
      }

      // Solve modified diffusion equation for all propagators
      int monomerId;
      for (int j = 0; j < nPropagator(); ++j) {
         if (!propagator(j).isReady()) {
            UTIL_THROW("Propagator not ready");
         }
         monomerId = propagator(j).block().monomerId();
         propagator(j).solve(wFields[monomerId]);
      }

      // Compute molecular partition function
      double q = propagator(0,0).computeQ();
      if (ensemble() == Species::Closed) {
         mu_ = log(phi_/q);
      } 
      else if (ensemble() == Species::Open) {
         phi_ = exp(mu_)*q;
      }

      // Compute block concentration fields
      double prefactor = phi_ / (q*length());
      for (int i = 0; i < nBlock(); ++i) {
         propagator(i, 0).computeConcentration(prefactor, blockCFields_[i]);
      }

   }
 
}
#endif
