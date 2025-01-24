library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use IEEE.NUMERIC_STD.ALL;
entity tb_cache is
end tb_cache;
architecture Behavioral of tb_cache is
component cache_memory
Port (
clk : in STD_LOGIC;
reset : in STD_LOGIC;
address : in STD_LOGIC_VECTOR(15 downto 0);
data_in : in STD_LOGIC_VECTOR(31 downto 0);
write_enable : in STD_LOGIC;
data_out : out STD_LOGIC_VECTOR(31 downto 0);
hit : out STD_LOGIC
);
end component;
constant T : time := 10 ns;
-- Semnale interne
signal clk : STD_LOGIC := '0';
signal reset : STD_LOGIC := '0';
signal address : STD_LOGIC_VECTOR(15 downto 0) := (others => '0');
signal data_in : STD_LOGIC_VECTOR(31 downto 0) := (others => '0');
signal write_enable : STD_LOGIC := '0';
signal data_out : STD_LOGIC_VECTOR(31 downto 0);
signal hit : STD_LOGIC;
begin
uut: cache_memory
Port map (
clk => clk,
reset => reset,
address => address,
data_in => data_in,
write_enable => write_enable,
data_out => data_out,
hit => hit
);
clk_process: process
begin
while true loop
clk <= '0';
wait for T / 2;
clk <= '1';
wait for T / 2;
end loop;
end process;
stimulus: process
begin
reset <= '1';
wait for T;
reset <= '0';
address <= x"0123";
data_in <= x"12345678";
write_enable <= '1';
wait for T;
write_enable <= '0';
address <= x"0123";
wait for T;
address <= x"0223";
wait for T;
address <= x"0345";
data_in <= x"ABCDEFAB";
write_enable <= '1';
wait for T;
write_enable <= '0';
address <= x"0345";
wait for T;
wait;
end process;
end Behavioral;