LIBRARY ieee;
USE ieee.std_logic_1164.all;
use ieee.std_logic_unsigned.all;

ENTITY muxn_1 IS
  PORT (
	--generic (...)
	--8:1 pt. ca nu merge generic
	--logica la generic va implica ceil(log2(n)) pentru a gasi nr. de biti necesari pentru selectie 
	A : in std_logic_vector(7 downto 0);
	SEL : in std_logic_vector(3 downto 1);
	Y : out std_logic
    );
END muxn_1;

ARCHITECTURE TypeArchitecture OF muxn_1 IS

BEGIN
	Y <= A(conv_integer(SEL));

END TypeArchitecture;
