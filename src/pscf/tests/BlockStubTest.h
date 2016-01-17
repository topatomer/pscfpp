#ifndef BLOCK_STUB_TEST_H
#define BLOCK_STUB_TEST_H

#include <test/UnitTest.h>
#include <test/UnitTestRunner.h>

#include "BlockStub.h"

#include <fstream>

using namespace Pscf;
//using namespace Util;

class BlockStubTest : public UnitTest 
{

public:

   void setUp()
   {}

   void tearDown()
   {}

  
   void testConstructor()
   {
      printMethod(TEST_FUNC);
      BlockStub v;
   } 

   void testReadWrite() {
      printMethod(TEST_FUNC);
      printEndl();

      BlockStub v;
      std::ifstream in;
      openInputFile("in/BlockStub", in);

      in >> v;
      TEST_ASSERT(v.id() == 5);
      TEST_ASSERT(v.monomerId() == 0);
      TEST_ASSERT(v.vertexId(0) == 3);
      TEST_ASSERT(v.vertexId(1) == 4);
      TEST_ASSERT(eq(v.length(), 2.0));
      // std::cout << v << std::endl ;
   }

};

TEST_BEGIN(BlockStubTest)
TEST_ADD(BlockStubTest, testConstructor)
TEST_ADD(BlockStubTest, testReadWrite)
TEST_END(BlockStubTest)

#endif