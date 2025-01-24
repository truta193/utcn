library IEEE;
use IEEE.STD_LOGIC_1164.all;
use IEEE.NUMERIC_STD.all;

entity fifo_ctrl is
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
end fifo_ctrl;

architecture Behavioral of fifo_ctrl is
	signal read_ptr : unsigned(2 downto 0) := (others => '0');
	signal write_ptr : unsigned(2 downto 0) := (others => '0');
	signal count : unsigned(3 downto 0) := (others => '0');

	signal rd_prev : std_logic := '0';
	signal wr_prev : std_logic := '0';

begin
	process (clk, rst)
	begin
		if rst = '1' then
			read_ptr <= (others => '0');
			write_ptr <= (others => '0');
			count <= (others => '0');
			rdinc <= '0';
			wrinc <= '0';
			empty <= '1';
			full <= '0';
			rd_prev <= '0';
			wr_prev <= '0';
		elsif rising_edge(clk) then
			rdinc <= '0';
			wrinc <= '0';

			if rd = '1' and rd_prev = '0' then
				if count > 0 then
					rdinc <= '1';
					read_ptr <= read_ptr + 1;
					count <= count - 1;
				end if;
			end if;

			if wr = '1' and wr_prev = '0' then
				if count < 8 then
					wrinc <= '1';
					write_ptr <= write_ptr + 1;
					count <= count + 1;
				end if;
			end if;

			rd_prev <= rd;
			wr_prev <= wr;

			if count = 0 then
				empty <= '1';
				full <= '0';
			elsif count = 8 then
				empty <= '0';
				full <= '1';
			else
				empty <= '0';
				full <= '0';
			end if;
		end if;
	end process;
end Behavioral;