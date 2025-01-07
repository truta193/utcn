LIBRARY ieee;
USE ieee.std_logic_1164.all;
use ieee.std_logic_unsigned.all;

ENTITY mem_rom IS
  PORT (
	A_ROM : in std_logic_vector(3 downto 0);
	CS_ROM : in std_logic;
	D_ROM : out std_logic_vector(7 downto 0)
    );
END mem_rom;


ARCHITECTURE comportm OF mem_rom IS
	type MATRIX is array(0 to 15) of std_logic_vector(7 downto 0);
	constant mem : MATRIX := (x"00", x"01", x"02", x"03", x"04", x"05", x"06", x"07", x"08", x"09", x"0A", x"0B", x"0C", x"0D", x"0E", x"0F");
	signal mat : MATRIX;
BEGIN
	mat <= mem;
	process(CS_ROM, A_ROM) 
	begin
		if (CS_ROM = '0') then
			D_ROM <= x"ff";
		else
			D_ROM <= mat(conv_integer(A_ROM));
		end if;
	
	end process;

END comportm;
