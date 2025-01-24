library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use IEEE.STD_LOGIC_ARITH.ALL;
use IEEE.STD_LOGIC_UNSIGNED.ALL;

entity final_tb is
end final_tb;

architecture Behavioral of final_tb is

component final is
    Port (
        aclk : IN STD_LOGIC;

        s_axis_val_tvalid : IN STD_LOGIC;
        s_axis_val_tready : OUT STD_LOGIC;
        s_axis_val_tdata : IN STD_LOGIC_VECTOR(31 DOWNTO 0);

        s_axis_max_tvalid : IN STD_LOGIC;
        s_axis_max_tready : OUT STD_LOGIC;
        s_axis_max_tdata : IN STD_LOGIC_VECTOR(31 DOWNTO 0);

        s_axis_min_tvalid : IN STD_LOGIC;
        s_axis_min_tready : OUT STD_LOGIC;
        s_axis_min_tdata : IN STD_LOGIC_VECTOR(31 DOWNTO 0);

        m_axis_sum_tvalid : OUT STD_LOGIC;
        m_axis_sum_tready : IN STD_LOGIC;
        m_axis_sum_tdata : OUT STD_LOGIC_VECTOR(31 DOWNTO 0)
    );
end component;

    signal aclk : STD_LOGIC := '0';

    signal s_axis_val_tvalid : STD_LOGIC := '0';
    signal s_axis_val_tready : STD_LOGIC;
    signal s_axis_val_tdata : STD_LOGIC_VECTOR(31 DOWNTO 0) := (others => '0');

    signal s_axis_max_tvalid : STD_LOGIC := '0';
    signal s_axis_max_tready : STD_LOGIC;
    signal s_axis_max_tdata : STD_LOGIC_VECTOR(31 DOWNTO 0) := (others => '0');

    signal s_axis_min_tvalid : STD_LOGIC := '0';
    signal s_axis_min_tready : STD_LOGIC;
    signal s_axis_min_tdata : STD_LOGIC_VECTOR(31 DOWNTO 0) := (others => '0');

    signal m_axis_sum_tvalid : STD_LOGIC;
    signal m_axis_sum_tready : STD_LOGIC := '1';
    signal m_axis_sum_tdata : STD_LOGIC_VECTOR(31 DOWNTO 0);

    constant clk_period : time := 10 ns;

begin

    fin: final
        port map (
            aclk => aclk,
            s_axis_val_tvalid => s_axis_val_tvalid,
            s_axis_val_tready => s_axis_val_tready,
            s_axis_val_tdata => s_axis_val_tdata,

            s_axis_max_tvalid => s_axis_max_tvalid,
            s_axis_max_tready => s_axis_max_tready,
            s_axis_max_tdata => s_axis_max_tdata,

            s_axis_min_tvalid => s_axis_min_tvalid,
            s_axis_min_tready => s_axis_min_tready,
            s_axis_min_tdata => s_axis_min_tdata,

            m_axis_sum_tvalid => m_axis_sum_tvalid,
            m_axis_sum_tready => m_axis_sum_tready,
            m_axis_sum_tdata => m_axis_sum_tdata
        );

    clk_process : process
    begin
        while true loop
            aclk <= '0';
            wait for clk_period / 2;
            aclk <= '1';
            wait for clk_period / 2;
        end loop;
    end process;

 process begin
        wait for 20 ns;


        s_axis_val_tdata <= X"00000010";
        s_axis_max_tdata <= X"00000020";
        s_axis_min_tdata <= X"00000005";
        s_axis_val_tvalid <= '1';
        s_axis_max_tvalid <= '1';
        s_axis_min_tvalid <= '1';
        wait for clk_period;

        s_axis_val_tvalid <= '0';
        s_axis_max_tvalid <= '0';
        s_axis_min_tvalid <= '0';
        wait for clk_period;

        s_axis_val_tdata <= X"00000030";
        s_axis_max_tdata <= X"00000020";
        s_axis_min_tdata <= X"00000005";
        s_axis_val_tvalid <= '1';
        s_axis_max_tvalid <= '1';
        s_axis_min_tvalid <= '1';
        wait for clk_period;

        s_axis_val_tvalid <= '0';
        s_axis_max_tvalid <= '0';
        s_axis_min_tvalid <= '0';
        wait for clk_period;

        s_axis_val_tdata <= X"00000003";
        s_axis_max_tdata <= X"00000020";
        s_axis_min_tdata <= X"00000005";
        s_axis_val_tvalid <= '1';
        s_axis_max_tvalid <= '1';
        s_axis_min_tvalid <= '1';
        wait for clk_period;

        s_axis_val_tvalid <= '0';
        s_axis_max_tvalid <= '0';
        s_axis_min_tvalid <= '0';

        wait;
    end process;

end Behavioral;
