LIBRARY ieee;
USE ieee.std_logic_1164.all;

ENTITY AND_GateN IS
	--GENERIC (NR_INTRARI: NATURAL := 2);
	--5 in loc de parametru generic
	port (
		A : in std_logic_vector(5 downto 1);
		B : out std_logic
	);

END AND_GateN;

--------------------------------------------------------------------------------
--Complete your VHDL description below
--------------------------------------------------------------------------------

ARCHITECTURE TypeArchitecture OF AND_GateN IS
	signal s : std_logic_vector(1 to 5) := (others => '1');
BEGIN
	process(A)
	begin
		if (s = A) then
		B <= '1';
		else
		B <= '0';
		end if;
	end process;

END TypeArchitecture;