library IEEE;
use IEEE.STD_LOGIC_1164.all;
use IEEE.NUMERIC_STD.all;

entity fifo_ctrl_tb is
end fifo_ctrl_tb;

architecture Behavioral of fifo_ctrl_tb is
	component fifo_ctrl
		port (
			rd     : in std_logic;
			wr     : in std_logic;
			clk    : in std_logic;
			rst    : in std_logic;
			rdinc  : out std_logic;
			wrinc  : out std_logic;
			empty  : out std_logic;
			full   : out std_logic
		);
	end component;

	signal rd : std_logic := '0';
	signal wr : std_logic := '0';
	signal clk : std_logic := '0';
	signal rst : std_logic := '0';
	signal rdinc : std_logic;
	signal wrinc : std_logic;
	signal empty : std_logic;
	signal full : std_logic;

	constant clk_period : time := 10 ns;

begin
	ctrl : fifo_ctrl
	port map(
		rd     => rd, 
		wr     => wr, 
		clk    => clk, 
		rst    => rst, 
		rdinc  => rdinc, 
		wrinc  => wrinc, 
		empty  => empty, 
		full   => full
	);
	process begin
	while true loop
	clk <= '0';
	wait for clk_period / 2;
	clk <= '1';
	wait for clk_period / 2;
end loop;
end process;

process begin
rst <= '1';
wait for clk_period * 2;
rst <= '0';
 
for i in 0 to 8 loop
	wr <= '1';
	wait for clk_period;

	wr <= '0';
	wait for clk_period;
end loop;

for i in 0 to 8 loop
	rd <= '1';
	wait for clk_period;
	rd <= '0';
	wait for clk_period;
end loop;

wait for clk_period;

wait;
end process;
end Behavioral;