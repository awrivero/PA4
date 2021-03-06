/****************************************************************************
 * Digital Circuit Synthesis Final Project
 * Controller, Datapath, and Testbench generation using Data Flow Graphs
 * 
 * Authors: Anthony Teresi, Mary Mouro, and Andy Rivero
 * 
 * Source File
 * This generates the VHDL controller
****************************************************************************/

#include "../header/controller_vhdl.h"

void controller_vhdl::create_vhdl_code (ostream &os)
{
	cout << "Creating Controller Entity\n";
	create_entity (os);
	cout << "Creating Controller Architecture\n";
	create_architecture (os);
}

void controller_vhdl::create_entity (ostream &os)
{
	os << "library IEEE;\n";
	os << "use IEEE.STD_LOGIC_1164.ALL;\n";
	os << "use ieee.numeric_std.all;\n\n";

	os << "entity " << entity_name << "_controller is\n";

	os << "port\n(\n";	

	// generate WR for the different registers
	for (const auto &r : dp.runits)
		if (!r.is_input)
			os << "\t" << r.WR_name << " : out std_logic;\n";

	// register multiplexers control signals
	for (const auto &mux : dp.reg_mux)
		if (mux.in.size() > 1)
			os << "\t" << mux.sel_name << " : out std_logic_vector(" << mux.sel_size - 1 << " downto 0);\n";

	// functional units multiplexers control signals
	for (const auto mux2 : dp.fu_mux)
	{
		if (mux2[0].in.size() > 1)
			os << "\t" << mux2[0].sel_name << " : out std_logic_vector(" << mux2[0].sel_size - 1 << " downto 0);\n";

		if (mux2[1].in.size() > 1)
			os << "\t" << mux2[1].sel_name << " : out std_logic_vector(" << mux2[1].sel_size - 1 << " downto 0);\n";
	}

	os << "\tstart : in std_logic;\n";
	os << "\tdone : out std_logic;\n";
	os << "\tclear : out std_logic;\n";
	os << "\tclock : in std_logic);\n";

	os << "end " << entity_name << "_controller;\n";
}

void controller_vhdl::create_architecture (ostream &os)
{
	os << "\narchitecture " << entity_name << "_controller_ar of " << entity_name << "_controller is\n";

	create_signals(os);

	os << "\nbegin\n";

	create_process (os);

	os << "end " << entity_name << "_controller_ar;\n";
}

void controller_vhdl::create_signals (ostream &os)
{
	os << "--------------------------- State controller --------------------------------\n";
	os <<"\tsignal state : integer range 0 to " << dp.max_timestep() + 1 << " := 0;\n";
}

void controller_vhdl::create_process (ostream &os)
{
	os <<"\tprocess (clock)\n";
	os <<"\tbegin\n";
	os <<"\t\tif rising_edge (clock) then\n";
	os << "\t\t\tcase state is\n";

	int mts = dp.max_timestep();
	
	for (int ts = 0; ts <= mts + 1; ts++)
	{
		os << "\t\t\t\twhen " << ts << " =>\n";

		for (const auto &s : contr.signal)
			if (s.ts == ts)
			{
				if (s.is_vector)
					os << "\t\t\t\t\t" << s.signal_name << " <= std_logic_vector(to_unsigned(" << s.val << ", " << s.w <<  "));\n";
				else
					os << "\t\t\t\t\t" << s.signal_name << " <= '" << s.val << "';\n"; 
			}

		if (ts == 0)
		{
			os << "\n\t\t\t\t\tif start = '1' then\n";
			os << "\t\t\t\t\t\tclear <= '1';\n";
			os << "\t\t\t\t\t\tstate <= 1;\n";
			os << "\t\t\t\t\tend if;\n\n";
		}
		else 
		{
			if (ts == 1)
				os << "\t\t\t\t\tclear <= '0';\n";

			if (ts < mts + 1)
				os << "\t\t\t\t\tstate <= " << ts + 1 << ";\n\n";
			else
				os << "\t\t\t\t\tstate <= 0;\n\n";
		}
	}

	os << "\t\t\tend case;\n"; 	
	os <<"\t\tend if;\n";
	os <<"\tend process;\n";
}