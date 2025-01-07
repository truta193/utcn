
LIBRARY ieee;
USE ieee.std_logic_1164.ALL;

ENTITY sumator IS
	PORT (
		A, B, CIN : IN std_logic;
		S, COUT : OUT std_logic
	);
END sumator;

ARCHITECTURE flux OF sumator IS

BEGIN
	S <= A XOR B XOR CIN;
	COUT <= (A AND B) OR (A AND CIN) OR (B AND CIN);

END flux;