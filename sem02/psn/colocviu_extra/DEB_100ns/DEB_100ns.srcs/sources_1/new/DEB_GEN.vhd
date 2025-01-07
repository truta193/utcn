
LIBRARY ieee;
USE ieee.std_logic_1164.all;

ENTITY debouncer_100ns IS
  PORT (
	clk, inp: in std_logic;
	o: out std_logic;
	w: out std_logic_vector(9 downto 0)
    );
END debouncer_100ns;


ARCHITECTURE TypeArchitecture OF debouncer_100ns IS

component bistabil_d IS
  PORT (
	clk, r,d: in std_logic;
	q: out std_logic
    );
END component;
signal wires: std_logic_vector(9 downto 0);
BEGIN
B1: bistabil_d port map(clk, '0', inp, wires(0));

GEN: for i in 1 to 9 generate
	BI: bistabil_d port map (clk, '0', wires(i-1), wires(i));
end generate;

o <= wires(0) and wires(1) and wires(2) and wires(3) and wires(4) and wires(5) and wires(6) and wires(7) and wires(8) and wires(9);
w <= wires;
END TypeArchitecture;


----------------- BISTABIL D ----------------------

LIBRARY ieee;
USE ieee.std_logic_1164.all;

ENTITY bistabil_d IS
  PORT (
	clk, r,d: in std_logic;
	q: out std_logic
    );
END bistabil_d;


ARCHITECTURE TypeArchitecture OF bistabil_d IS
	
BEGIN
	process(clk)
	begin
	if r = '1' then
		q <= '0';
	elsif rising_edge(clk) then
		q <= d;
	end if;
	end process;

END TypeArchitecture;

