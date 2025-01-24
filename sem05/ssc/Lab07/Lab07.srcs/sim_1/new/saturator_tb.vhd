library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use IEEE.STD_LOGIC_UNSIGNED.ALL;

entity saturator_tb is
end saturator_tb;

architecture Behavioral of saturator_tb is
    component saturator
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
            m_axis_result_tvalid : OUT STD_LOGIC;
            m_axis_result_tready : IN STD_LOGIC;
            m_axis_result_tdata : OUT STD_LOGIC_VECTOR(31 DOWNTO 0)
        );
    end component;

    -- Test signals
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
    
    signal m_axis_result_tvalid : STD_LOGIC;
    signal m_axis_result_tready : STD_LOGIC := '0';
    signal m_axis_result_tdata : STD_LOGIC_VECTOR(31 DOWNTO 0);

    constant clk_period : time := 10 ns;
begin
    satr: saturator
        Port map (
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
            m_axis_result_tvalid => m_axis_result_tvalid,
            m_axis_result_tready => m_axis_result_tready,
            m_axis_result_tdata => m_axis_result_tdata
        );

    clk_process : process
    begin
        aclk <= '0';
        wait for clk_period / 2;
        aclk <= '1';
        wait for clk_period / 2;
    end process;

    stim_proc: process
    begin
        s_axis_val_tdata <= x"00000010";
        s_axis_min_tdata <= x"00000005";
        s_axis_max_tdata <= x"00000020";
        s_axis_val_tvalid <= '1';
        s_axis_min_tvalid <= '1';
        s_axis_max_tvalid <= '1';
        m_axis_result_tready <= '1';
        wait for clk_period;

        wait until (m_axis_result_tvalid = '1');

        s_axis_val_tdata <= x"00000025";
        wait for clk_period;

        wait until (m_axis_result_tvalid = '1');

        s_axis_val_tdata <= x"00000002";
        wait for clk_period;

        wait until (m_axis_result_tvalid = '1');

        wait;
    end process;
end Behavioral;