library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use IEEE.NUMERIC_STD.ALL;
entity line_decoder is
Port (
index : in STD_LOGIC_VECTOR(5 downto 0);
select_line : out STD_LOGIC_VECTOR(63 downto 0)
);
end line_decoder;
architecture Behavioral of line_decoder is
begin
process(index)
begin
select_line <= (others => '0');
select_line(to_integer(unsigned(index))) <= '1';
end process;
end Behavioral;