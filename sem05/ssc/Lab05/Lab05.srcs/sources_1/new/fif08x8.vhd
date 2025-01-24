library IEEE;
use IEEE.STD_LOGIC_1164.all;
use IEEE.STD_LOGIC_ARITH.all;
use IEEE.STD_LOGIC_UNSIGNED.all;

entity fifo8x8 is
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
end fifo8x8;

architecture Behavioral of fifo8x8 is

	component cnt is
		port (
			en   : in std_logic;
			clk  : in std_logic;
			ld   : in std_logic;
			q    : out std_logic_vector(2 downto 0)
		);
	end component;

	component reg is
		port (
			d    : in STD_LOGIC_VECTOR(7 downto 0);
			ld   : in STD_LOGIC;
			clr  : in STD_LOGIC;
			clk  : in STD_LOGIC;
			q    : out STD_LOGIC_VECTOR(7 downto 0)
		);
	end component;

	signal mux_sgn : std_logic_vector(7 downto 0) := "00000000";
	signal write_ptr : std_logic_vector(2 downto 0) := "000";
	signal read_ptr : std_logic_vector(2 downto 0) := "000";
	signal dec_sgn : std_logic_vector(7 downto 0) := "00000000";
	type byte_array is array (0 to 7) of std_logic_vector(7 downto 0);
	signal fifo_sgn : byte_array := (others => (others => '0'));
	signal intermediate_ld : std_logic_vector(7 downto 0) := "00000000";
	signal outpt : std_logic_vector(7 downto 0) := "ZZZZZZZZ";

begin
	write_ptr_cnt : cnt
	port map(wrinc, clk, rst, write_ptr);
	read_ptr_cnt : cnt
	port map(rdinc, clk, rst, read_ptr);
 

	process (clk)
begin
	if rising_edge(clk) then
		if (rst = '1') then
			dec_sgn <= "00000000";
		else
			case write_ptr is
				when "000" => dec_sgn <= "00000001";
				when "001" => dec_sgn <= "00000010";
				when "010" => dec_sgn <= "00000100";
				when "011" => dec_sgn <= "00001000";
				when "100" => dec_sgn <= "00010000";
				when "101" => dec_sgn <= "00100000";
				when "110" => dec_sgn <= "01000000";
				when "111" => dec_sgn <= "10000000";
				when others => dec_sgn <= "00000000";
			end case;
		end if;
	end if;
end process;
 

RegisterArray : for i in 0 to 7 generate
	intermediate_ld(i) <= wr and dec_sgn(i);
	Register_inst : reg
	port map(data_in, intermediate_ld(i), rst, clk, fifo_sgn(i));
end generate RegisterArray;
 

process (read_ptr) begin
case read_ptr is
	when "000" => outpt <= fifo_sgn(0);
	when "001" => outpt <= fifo_sgn(1);
	when "010" => outpt <= fifo_sgn(2);
	when "011" => outpt <= fifo_sgn(3);
	when "100" => outpt <= fifo_sgn(4);
	when "101" => outpt <= fifo_sgn(5);
	when "110" => outpt <= fifo_sgn(6);
	when "111" => outpt <= fifo_sgn(7);
	when others => outpt <= "ZZZZZZZZ";
end case;
end process;
 
process (rd, outpt) begin
if rd = '1' then
	data_out <= outpt;
else
	data_out <= "ZZZZZZZZ";
end if;
end process;
 
end Behavioral;