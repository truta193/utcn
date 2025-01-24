library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use IEEE.NUMERIC_STD.ALL;

entity data_memory is
Port (
clk : in STD_LOGIC;
reset : in STD_LOGIC;
index : in STD_LOGIC_VECTOR(5 downto 0);
data_in : in STD_LOGIC_VECTOR(31 downto 0);
write_enable : in STD_LOGIC;
data_out : out STD_LOGIC_VECTOR(31 downto 0)
);

end data_memory;
architecture Behavioral of data_memory is
type data_array is array (0 to 63) of STD_LOGIC_VECTOR(31 downto 0);
signal data : data_array := (others => (others => '0'));
begin
process(clk, reset)
begin
if reset = '1' then
data <= (others => (others => '0'));
elsif rising_edge(clk) then
if write_enable = '1' then
data(to_integer(unsigned(index))) <= data_in;
end if;
end if;
end process;
data_out <= data(to_integer(unsigned(index)));
end Behavioral;