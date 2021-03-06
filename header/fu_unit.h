/****************************************************************************
 * Digital Circuit Synthesis Final Project
 * Controller, Datapath, and Testbench generation using Data Flow Graphs
 * 
 * Authors: Anthony Teresi, Mary Mouro, and Andy Rivero
 * 
 * Header File
 * This represents a functional unit
****************************************************************************/

#ifndef FU_UNIT_H
#define FU_UNIT_H

#include <string>
#include <vector>
#include "operation.h"

using std::string;

struct fu_unit
{
	string fu_name, i1_name, i2_name, out_name;
	int w;
	operation_type type;
	vector<int> i[2], out, ts;

	fu_unit () = default;
	fu_unit (string fu_name, string i1_name, string i2_name, string out_name, int w, operation_type type)
		: fu_name (fu_name), i1_name (i1_name), i2_name (i2_name), out_name (out_name), w (w), type (type) {}
};

#endif