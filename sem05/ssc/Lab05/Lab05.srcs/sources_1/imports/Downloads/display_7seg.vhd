library IEEE;
use IEEE.STD_LOGIC_1164.all;
use IEEE.STD_LOGIC_ARITH.all;
use IEEE.STD_LOGIC_UNSIGNED.all;

entity display_7seg is
	port (
		digit0  : in STD_LOGIC_VECTOR (3 downto 0);
		digit1  : in STD_LOGIC_VECTOR (3 downto 0);
		digit2  : in STD_LOGIC_VECTOR (3 downto 0);
		digit3  : in STD_LOGIC_VECTOR (3 downto 0);
		clk     : in STD_LOGIC;
		cat     : out STD_LOGIC_VECTOR (6 downto 0);
		an      : out STD_LOGIC_VECTOR (3 downto 0)
	);
end display_7seg;

architecture Behavioral of display_7seg is

	signal cnt : STD_LOGIC_VECTOR (2 downto 0) := (others => '0');
	signal digit_to_display : STD_LOGIC_VECTOR (3 downto 0) := (others => '0');

begin
	process (clk)
	begin
		if rising_edge(clk) then
			cnt <= cnt + 1;
		end if;
	end process;
 
	digit_to_display <= digit0 when cnt(2 downto 1) = "00" else
	                    digit1 when cnt(2 downto 1) = "01" else
	                    digit2 when cnt(2 downto 1) = "10" else
	                    digit3;
 
	an <= "1110" when cnt(2 downto 1) = "00" else
	      "1101" when cnt(2 downto 1) = "01" else
	      "1011" when cnt(2 downto 1) = "10" else
	      "0111";
 




 
	with digit_to_display select
	cat <= "1111001" when "0001", 
	       "0100100" when "0010", 
	       "0110000" when "0011", 
	       "0011001" when "0100", 
	       "0010010" when "0101", 
	       "0000010" when "0110", 
	       "1111000" when "0111", 
	       "0000000" when "1000", 
	       "0010000" when "1001", 
	       "0001000" when "1010", 
	       "0000011" when "1011", 
	       "1000110" when "1100", 
	       "0100001" when "1101", 
	       "0000110" when "1110", 
	       "0001110" when "1111", 
	       "1000000" when others; 

end Behavioral;