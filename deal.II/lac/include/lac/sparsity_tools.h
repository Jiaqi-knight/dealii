//---------------------------------------------------------------------------
//    $Id: sparsity_tools.h 16733 2008-09-03 14:22:26Z heister $
//    Version: $Name$
//
//    Copyright (C) 2008 by the deal.II authors
//
//    This file is subject to QPL and may not be  distributed
//    without copyright and license information. Please refer
//    to the file deal.II/doc/license.html for the  text  and
//    further information on this license.
//
//---------------------------------------------------------------------------
#ifndef __deal2__sparsity_tools_h
#define __deal2__sparsity_tools_h


#include <base/config.h>
#include <base/exceptions.h>

DEAL_II_NAMESPACE_OPEN

class SparsityPattern;



/*! @addtogroup Sparsity
 *@{
 */

/**
 * A namespace for functions that deal with things that one can do on sparsity
 * patterns, such as renumbering rows and columns (or degrees of freedom if
 * you want) according to the connectivity, or partitioning degrees of
 * freedom.
*/
namespace SparsityTools
{
				   /**
				    * Use the METIS partitioner to generate
				    * a partitioning of the degrees of
				    * freedom represented by this sparsity
				    * pattern. In effect, we view this
				    * sparsity pattern as a graph of
				    * connections between various degrees of
				    * freedom, where each nonzero entry in
				    * the sparsity pattern corresponds to an
				    * edge between two nodes in the
				    * connection graph. The goal is then to
				    * decompose this graph into groups of
				    * nodes so that a minimal number of
				    * edges are cut by the boundaries
				    * between node groups. This partitioning
				    * is done by METIS. Note that METIS can
				    * only partition symmetric sparsity
				    * patterns, and that of course the
				    * sparsity pattern has to be square. We
				    * do not check for symmetry of the
				    * sparsity pattern, since this is an
				    * expensive operation, but rather leave
				    * this as the responsibility of caller
				    * of this function.
				    *
				    * After calling this function, the
				    * output array will have values between
				    * zero and @p n_partitions-1 for each
				    * node (i.e. row or column of the
				    * matrix).
				    *
				    * This function will generate an error
				    * if METIS is not installed unless
				    * @p n_partitions is one. I.e., you can
				    * write a program so that it runs in the
				    * single-processor single-partition case
				    * without METIS installed, and only
				    * requires METIS when multiple
				    * partitions are required.
				    *
				    * Note that the sparsity pattern itself
				    * is not changed by calling this
				    * function. However, you will likely use
				    * the information generated by calling
				    * this function to renumber degrees of
				    * freedom, after which you will of
				    * course have to regenerate the sparsity
				    * pattern.
				    *
				    * This function will rarely be called
				    * separately, since in finite element
				    * methods you will want to partition the
				    * mesh, not the matrix. This can be done
				    * by calling
				    * @p GridTools::partition_triangulation.
				    */
  void partition (const SparsityPattern     &sparsity_pattern,
		  const unsigned int         n_partitions,
		  std::vector<unsigned int> &partition_indices);

				   /**
				    * Exception
				    */
  DeclException0 (ExcMETISNotInstalled);
				   /**
				    * Exception
				    */
  DeclException1 (ExcInvalidNumberOfPartitions,
		  int,
		  << "The number of partitions you gave is " << arg1
		  << ", but must be greater than zero.");
				   /**
				    * Exception
				    */
  DeclException2 (ExcInvalidArraySize,
		  int, int,
		  << "The array has size " << arg1 << " but should have size "
		  << arg2);
}

/**
 *@}
 */

DEAL_II_NAMESPACE_CLOSE

#endif
