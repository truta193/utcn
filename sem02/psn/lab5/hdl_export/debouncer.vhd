LIBRARY ieee;
USE ieee.std_logic_1164.all;
USE ieee.std_logic_unsigned.all;

ENTITY debouncer IS
  PORT (
	CLK, BTN: in std_logic;
	BTN_DB: out std_logic
    );
END debouncer;


ARCHITECTURE structr OF debouncer IS
	component bistabil_d is
	  PORT (
		CLK: in std_logic;
		D, S, R: in std_logic;
		Q: out std_logic
	    );
	END component;

	component POARTA_SI is
		PORT (
		X, Y, Z : IN std_logic;
		W : OUT std_logic
		);
	END component;

	signal Q2, Q1, Q0: std_logic;

BEGIN
	AP : POARTA_SI port map (Q2, Q1, Q0, BTN_DB);
	D1 : bistabil_d port map(CLK, BTN, '1', '1', Q2);
	D2 : bistabil_d port map(CLK, Q2, '1', '1', Q1);
	D3 : bistabil_d port map(CLK, Q1, '1', '1', Q0);

END structr;




----------- BISTABIL D ---------------------------



LIBRARY ieee;
USE ieee.std_logic_1164.all;
USE ieee.std_logic_unsigned.all;

ENTITY bistabil_d IS
  PORT (
	CLK: in std_logic;
	D, S, R: in std_logic;
	Q: out std_logic
    );
END bistabil_d;


ARCHITECTURE compr OF bistabil_d IS

BEGIN

	process(CLK)
	begin
		if rising_edge(CLK) then
			if (S = '0') then
				Q <= '1';
			elsif (R = '0') then
				Q <= '0';
			else 
				Q <= D;
			end if;
		end if;
	end process;

END compr;






--------------- POARTA SI ----------------------

LIBRARY ieee;
USE ieee.std_logic_1164.ALL;
ENTITY POARTA_SI IS
	PORT (
	X, Y, Z : IN std_logic;
	W : OUT std_logic
	);
END ENTITY;

ARCHITECTURE flux OF POARTA_SI IS
BEGIN
	W <= X AND Y AND Z;
END ARCHITECTURE;
