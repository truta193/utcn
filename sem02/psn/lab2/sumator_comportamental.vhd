LIBRARY ieee;
USE ieee.std_logic_1164.ALL;

ENTITY sumator IS
	PORT (
		A, B, CIN : IN std_logic;
		S, COUT : OUT std_logic
	);
END sumator;
ARCHITECTURE comportamental OF sumator IS

BEGIN
	PROCESS (A, B, CIN)
	BEGIN
		IF A = '0' AND B = '0' AND CIN = '0' THEN
			COUT <= '0';
			S <= '0';
		ELSIF A = '0' AND B = '0' AND CIN = '1' THEN
			COUT <= '0';
			S <= '1';
		ELSIF A = '0' AND B = '1' AND CIN = '0' THEN
			COUT <= '0';
			S <= '1';
		ELSIF A = '0' AND B = '1' AND CIN = '1' THEN
			COUT <= '1';
			S <= '0';
		ELSIF A = '1' AND B = '0' AND CIN = '0' THEN
			COUT <= '0';
			S <= '1';
		ELSIF A = '1' AND B = '0' AND CIN = '1' THEN
			COUT <= '1';
			S <= '0';
		ELSIF A = '1' AND B = '1' AND CIN = '0' THEN
			COUT <= '1';
			S <= '0';
		ELSE
			COUT <= '1';
			S <= '1';
		END IF;
	END PROCESS;

END comportamental;