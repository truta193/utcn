library IEEE;
use IEEE.STD_LOGIC_1164.all;
use IEEE.NUMERIC_STD.all;

entity tb_fifo is
end tb_fifo;

architecture Behavioral of tb_fifo is
	component fifo8x8
		port (
			clk       : in std_logic;
			rst       : in std_logic;
			wrinc     : in std_logic;
			rdinc     : in std_logic;
			rd        : in std_logic;
			wr        : in std_logic;
			data_in   : in std_logic_vector(7 downto 0);
			data_out  : out std_logic_vector(7 downto 0)
		);
	end component;

	signal clk : std_logic := '0';
	signal rst : std_logic := '0';
	signal wrinc : std_logic := '0';
	signal rdinc : std_logic := '0';
	signal rd : std_logic := '0';
	signal wr : std_logic := '0';
	signal data_in : std_logic_vector(7 downto 0) := (others => '0');
	signal data_out : std_logic_vector(7 downto 0);

	constant clk_period : time := 10 ns;

begin
	ffo : fifo8x8
	port map(
		clk       => clk, 
		rst       => rst, 
		wrinc     => wrinc, 
		rdinc     => rdinc, 
		rd        => rd, 
		wr        => wr, 
		data_in   => data_in, 
		data_out  => data_out
	);
	process begin
	clk <= '0';
	wait for clk_period / 2;
	clk <= '1';
	wait for clk_period / 2;
end process;

process begin
rst <= '1';
wait for clk_period;
rst <= '0';

wr <= '1';
for i in 0 to 7 loop
	data_in <= std_logic_vector(to_unsigned(i, 8));
	wrinc <= '1';
	wait for clk_period;
	wrinc <= '0';
	wait for clk_period;
end loop;
wr <= '0';

rd <= '1';
for i in 0 to 7 loop
	rdinc <= '1';
	wait for clk_period;
	rdinc <= '0';
	wait for clk_period;
end loop;
rd <= '0';
 
wait for 20 * clk_period;
wait;
end process;
end Behavioral;