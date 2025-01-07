LIBRARY ieee;
USE ieee.std_logic_1164.all;
USE ieee.std_logic_unsigned.all;

ENTITY mem_ram IS
  PORT (
	A_RAM : in std_logic_vector(3 downto 0);
	WE : in std_logic;
	D_RAM : in std_logic_vector(7 downto 0);
	CS_RAM : in std_logic;
	Y_RAM : out std_logic_vector(7 downto 0)
    );
END mem_ram;

--------------------------------------------------------------------------------
--Complete your VHDL description below
--------------------------------------------------------------------------------

ARCHITECTURE compl OF mem_ram IS
	type MATRIX is array(0 to 15) of std_logic_vector(7 downto 0);
	signal mat : MATRIX := (others => x"00");
BEGIN
	process(A_RAM, WE, D_RAM, CS_RAM)
	begin
		if (CS_RAM = '0') then
			Y_RAM <= x"ff";
		else
			if (WE = '0') then
				Y_RAM <= mat(conv_integer(A_RAM));
			else
				mat(conv_integer(A_RAM)) <= D_RAM;
				--Y_RAM <= x"ff";
				Y_RAM <= mat(conv_integer(A_RAM));
			end if;
		end if;
	end process;

END compl;
