#include <iostream>
#include <fstream>
#include "graph.h"
#include "datapath.h"

using std::cout;
using std::endl;
using std::ostream;

using vec2d = vector<vector<int>>;

class datapath_vhdl
{
private:
	void create_entity (ostream &);	
	void create_architecture (ostream &);
	void create_signals (ostream &);
	void create_registers (ostream &);
	void create_funits (ostream &);
	void create_reg_mux (ostream &);
	void create_fu_mux (ostream &);
	void create_output (ostream &);

public:
	datapath &dp;
	graph &g;
	string entity_name;

	datapath_vhdl (graph &g, datapath &dp, string entity_name) 
		: g (g), dp (dp), entity_name(entity_name) {}
	void create_vhdl_code (ostream &);
};