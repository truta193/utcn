library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use IEEE.NUMERIC_STD.ALL;
entity tag_memory is
Port (
clk : in STD_LOGIC;
reset : in STD_LOGIC;
index : in STD_LOGIC_VECTOR(5 downto 0);
tag_in : in STD_LOGIC_VECTOR(7 downto 0);
valid_in : in STD_LOGIC;
write_enable : in STD_LOGIC;
tag_out : out STD_LOGIC_VECTOR(7 downto 0);
valid_out : out STD_LOGIC
);
end tag_memory;
architecture Behavioral of tag_memory is
type tag_array is array (0 to 63) of STD_LOGIC_VECTOR(7 downto 0);
type valid_array is array (0 to 63) of STD_LOGIC;
signal tags : tag_array := (others => (others => '0'));
signal valid_bits : valid_array := (others => '0');
begin
process(clk, reset)
begin
if reset = '1' then
tags <= (others => (others => '0'));
valid_bits <= (others => '0');
elsif rising_edge(clk) then
if write_enable = '1' then
tags(to_integer(unsigned(index))) <= tag_in;
valid_bits(to_integer(unsigned(index))) <= valid_in;
end if;
end if;
end process;
tag_out <= tags(to_integer(unsigned(index)));
valid_out <= valid_bits(to_integer(unsigned(index)));
end Behavioral;