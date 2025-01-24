library IEEE;
use IEEE.STD_LOGIC_1164.all;
use IEEE.STD_LOGIC_ARITH.all;
use IEEE.NUMERIC_STD.all;

entity tb_final is
end tb_final;

architecture testbench of tb_final is
	component final is
		port (
			data_in  : in std_logic_vector(7 downto 0);
			btn_rd   : in std_logic;
			btn_wr   : in std_logic;
			clk      : in std_logic;
			rst      : in std_logic;
			cat      : out std_logic_vector(6 downto 0);
			an       : out std_logic_vector(3 downto 0);
			empty    : out std_logic;
			full     : out std_logic
		);
	end component;
 
	signal data_in : std_logic_vector(7 downto 0);
	signal btn_rd : std_logic;
	signal btn_wr : std_logic;
	signal clk : std_logic := '0';
	signal rst : std_logic;
	signal cat : std_logic_vector(6 downto 0);
	signal an : std_logic_vector(3 downto 0);
	signal empty : std_logic;
	signal full : std_logic;

	constant CLK_PERIOD : time := 10 ns;

begin
	fin : final
	port map(
		data_in  => data_in, 
		btn_rd   => btn_rd, 
		btn_wr   => btn_wr, 
		clk      => clk, 
		rst      => rst, 
		cat      => cat, 
		an       => an, 
		empty    => empty, 
		full     => full
	);
	process
	begin
		while true loop
		clk <= '0';
		wait for CLK_PERIOD / 2;
		clk <= '1';
		wait for CLK_PERIOD / 2;
	end loop;
	end process;

	process begin
	data_in <= (others => '0');
	btn_rd <= '0';
	btn_wr <= '0';
	rst <= '1';
	wait for 20 ns;

	rst <= '0';
	wait for 20 ns;

	for i in 0 to 15 loop
		data_in <= std_logic_vector(to_unsigned(i, 8));
		btn_wr <= '1';
		wait for 20 ns;
		btn_wr <= '0';
		wait for 20 ns;
	end loop;

	for i in 0 to 15 loop
		btn_rd <= '1';
		wait for 20 ns;
		btn_rd <= '0';
		wait for 20 ns;
	end loop;

	wait;
end process;

end testbench;