/*
 * Copyright (c) 2015 Carnegie Mellon University and The Trustees of Indiana
 * University.
 * All Rights Reserved.
 *
 * THIS SOFTWARE IS PROVIDED "AS IS," WITH NO WARRANTIES WHATSOEVER. CARNEGIE
 * MELLON UNIVERSITY AND THE TRUSTEES OF INDIANA UNIVERSITY EXPRESSLY DISCLAIM
 * TO THE FULLEST EXTENT PERMITTED BY LAW ALL EXPRESS, IMPLIED, AND STATUTORY
 * WARRANTIES, INCLUDING, WITHOUT LIMITATION, THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE, AND NON-INFRINGEMENT OF PROPRIETARY RIGHTS.
 *
 * This Program is distributed under a BSD license.  Please see LICENSE file or
 * permission@sei.cmu.edu for more information.  DM-0002659
 */

#include <iostream>

#include <algorithms/metrics.hpp>
#include <graphblas/graphblas.hpp>

using namespace graphblas;
using namespace algorithms;

#define BOOST_TEST_MAIN
#define BOOST_TEST_MODULE metrics_suite

#include <boost/test/included/unit_test.hpp>

BOOST_AUTO_TEST_SUITE(metrics_suite)

static double const INF = std::numeric_limits<double>::max();

static std::vector<double> gr={0,1,1,2,2,2,2,3,3,3,3,4,4,4,5,6,6,6,8,8};
static std::vector<double> gc={3,3,6,4,5,6,8,0,1,4,6,2,3,8,2,1,2,3,2,4};
static std::vector<double> gv(gr.size(), 1);

static Matrix<double, DirectedMatrixTag> G_tn(9,9);


//static Matrix<double, DirectedMatrixTag> G_tn_answer(
//    {{2, 2, 3, 1, 2, 4, 2, INF, 3},
//     {2, 2, 2, 1, 2, 3, 1, INF, 3},
//     {3, 2, 2, 2, 1, 1, 1, INF, 1},
//     {1, 1, 2, 2, 1, 3, 1, INF, 2},
//     {2, 2, 1, 1, 2, 2, 2, INF, 1},
//     {4, 3, 1, 3, 2, 2, 2, INF, 2},
//     {2, 1, 1, 1, 2, 2, 2, INF, 2},
//     {INF, INF, INF, INF, INF, INF, INF, INF, INF},
//     {3, 3, 1, 2, 1, 2, 2, INF, 2}},
//    INF);

static std::vector<double> tr={0,0,1,1,2,2,2,2,3,3,4,4};
static std::vector<double> tc={1,2,0,2,0,1,3,4,2,4,2,3};
static std::vector<double> tv(tr.size(), 1);

//static Matrix<double, DirectedMatrixTag> test5x5(
//    {{INF,   1,   1, INF, INF},
//     {  1, INF,   1, INF, INF},
//     {  1,   1, INF,   1,   1},
//     {INF, INF,   1, INF,   1},
//     {INF, INF,   1,   1, INF}},
//    INF);
static Matrix<double, DirectedMatrixTag> test5x5(5,5,INF);

BOOST_AUTO_TEST_CASE(metrics_test_vertex_count)
{
    graphblas::buildmatrix(G_tn, gr.begin(), gc.begin(), gv.begin(), gv.size());
    IndexType result = vertex_count(G_tn);
    BOOST_CHECK_EQUAL(result, 9);
}

BOOST_AUTO_TEST_CASE(metrics_test_edge_count)
{
    graphblas::buildmatrix(G_tn, gr.begin(), gc.begin(), gv.begin(), gv.size());
    IndexType result = edge_count(G_tn);
    BOOST_CHECK_EQUAL(result, 20);
}

BOOST_AUTO_TEST_CASE(metrics_test_in_degree)
{
    graphblas::buildmatrix(G_tn, gr.begin(), gc.begin(), gv.begin(), gv.size());
    IndexType result = vertex_in_degree(G_tn, 1);
    BOOST_CHECK_EQUAL(result, 2);
}

BOOST_AUTO_TEST_CASE(metrics_test_out_degree)
{
    graphblas::buildmatrix(G_tn, gr.begin(), gc.begin(), gv.begin(), gv.size());
    IndexType result = vertex_out_degree(G_tn, 2);
    BOOST_CHECK_EQUAL(result, 4);
}

BOOST_AUTO_TEST_CASE(metrics_test_vertex_degree)
{
    graphblas::buildmatrix(G_tn, gr.begin(), gc.begin(), gv.begin(), gv.size());
    IndexType result = vertex_degree(G_tn, 0);
    BOOST_CHECK_EQUAL(result, 2);
}

BOOST_AUTO_TEST_CASE(metrics_test_graph_distance)
{
    Matrix<double, DirectedMatrixTag> result(5, 5, INF);

    //Matrix<double, DirectedMatrixTag> answer(
    //    {{INF, INF, INF, INF, INF},
    //     {INF, INF, INF, INF, INF},
    //     {1, 1, 0, 1, 1},
    //     {INF, INF, INF, INF, INF},
    //     {INF, INF, INF, INF, INF}},
    //    INF);
    std::vector<double> ar={2,2,2,2,2};
    std::vector<double> ac={0,1,2,3,4};
    std::vector<double> av={1, 1, 0, 1, 1};
    Matrix<double, DirectedMatrixTag> answer(5,5,INF);
    graphblas::buildmatrix(answer, ar.begin(), ac.begin(), av.begin(), av.size());

    graphblas::buildmatrix(test5x5, tr.begin(), tc.begin(), tv.begin(), tv.size());
    graph_distance(test5x5, 2, result);
    BOOST_CHECK_EQUAL(result, answer);
}

BOOST_AUTO_TEST_CASE(metrics_test_graph_distance_matrix)
{
    Matrix<double, DirectedMatrixTag> result(5,5,INF);

    //Matrix<double, DirectedMatrixTag> answer(
    //    {{0, 1, 1, 2, 2},
    //     {1, 0, 1, 2, 2},
    //     {1, 1, 0, 1, 1},
    //     {2, 2, 1, 0, 1},
    //     {2, 2, 1, 1, 0}},
    //    INF);

    std::vector<double> ar={0,0,0,0,0,1,1,1,1,1,2,2,2,2,2,3,3,3,3,3,4,4,4,4,4};
    std::vector<double> ac={0,1,2,3,4,0,1,2,3,4,0,1,2,3,4,0,1,2,3,4,0,1,2,3,4};
    std::vector<double> av={0, 1, 1, 2, 2,
        1, 0, 1, 2, 2,
        1, 1, 0, 1, 1,
        2, 2, 1, 0, 1,
        2, 2, 1, 1, 0};
    Matrix<double, DirectedMatrixTag> answer(5,5,INF);
    graphblas::buildmatrix(answer, ar.begin(), ac.begin(), av.begin(), av.size());

    graphblas::buildmatrix(test5x5, tr.begin(), tc.begin(), tv.begin(), tv.size());
    graph_distance_matrix(test5x5, result);
    BOOST_CHECK_EQUAL(result, answer);
}

BOOST_AUTO_TEST_CASE(metrics_test_graph_eccentricity)
{
    graphblas::buildmatrix(test5x5, tr.begin(), tc.begin(), tv.begin(), tv.size());
    double result = vertex_eccentricity(test5x5, 2);
    BOOST_CHECK_EQUAL(result, 1);
}

BOOST_AUTO_TEST_CASE(metrics_test_graph_radius)
{
    graphblas::buildmatrix(test5x5, tr.begin(), tc.begin(), tv.begin(), tv.size());
    double result = graph_radius(test5x5);
    BOOST_CHECK_EQUAL(result, 1);
}

BOOST_AUTO_TEST_CASE(metrics_test_graph_diameter)
{
    graphblas::buildmatrix(test5x5, tr.begin(), tc.begin(), tv.begin(), tv.size());
    double result = graph_diameter(test5x5);
    BOOST_CHECK_EQUAL(result, 2);
}

BOOST_AUTO_TEST_CASE(metrics_test_degree_centrality)
{
    graphblas::buildmatrix(test5x5, tr.begin(), tc.begin(), tv.begin(), tv.size());
    IndexType result = degree_centrality(test5x5, 0);
    BOOST_CHECK_EQUAL(result, 4);
}

BOOST_AUTO_TEST_CASE(metrics_test_closeness_centrality)
{
    graphblas::buildmatrix(test5x5, tr.begin(), tc.begin(), tv.begin(), tv.size());
    double result = closeness_centrality(test5x5, 2);
    BOOST_CHECK_EQUAL(result, 4);
}


BOOST_AUTO_TEST_CASE(metrics_test_triangle_counting)
{
    //Matrix<double, DirectedMatrixTag> testtriangle({{0,1,1,1,0},
    //                        {1,0,1,0,1},
    //                        {1,1,0,1,1},
    //                        {1,0,1,0,1},
    //                        {0,1,1,1,0}});

    std::vector<double> ar={0, 0, 0, 1, 1, 1, 2, 2, 2, 2, 3, 3, 3, 4, 4, 4};
    std::vector<double> ac={1, 2, 3, 0, 2, 4, 0, 1, 3, 4, 0, 2, 4, 1, 2, 3};
    std::vector<double> av={1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1};
    Matrix<double, DirectedMatrixTag> testtriangle(5,5);
    graphblas::buildmatrix(testtriangle
            , ar.begin(), ac.begin(), av.begin(), av.size());

    IndexType result = triangle_count(testtriangle);
    BOOST_CHECK_EQUAL(result, 4);
}


BOOST_AUTO_TEST_SUITE_END()
