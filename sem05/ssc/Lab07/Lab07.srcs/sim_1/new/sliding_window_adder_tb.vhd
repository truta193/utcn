library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use IEEE.numeric_std.all;

entity sliding_window_adder_tb is
end sliding_window_adder_tb;

architecture test of sliding_window_adder_tb is
    constant WINDOW_SIZE : integer := 5;
    signal aclk               : std_logic := '0';
    signal s_axis_val_tvalid  : std_logic := '0';
    signal s_axis_val_tready  : std_logic;
    signal s_axis_val_tdata   : std_logic_vector(31 downto 0) := (others => '0');
    signal m_axis_sum_tvalid  : std_logic;
    signal m_axis_sum_tready  : std_logic := '1';
    signal m_axis_sum_tdata   : std_logic_vector(31 downto 0);

    component sliding_window_adder is
        Generic (
            WINDOW_SIZE : integer := 5
        );
        Port (
            aclk               : IN  STD_LOGIC;
            s_axis_val_tvalid  : IN  STD_LOGIC;
            s_axis_val_tready  : OUT STD_LOGIC;
            s_axis_val_tdata   : IN  STD_LOGIC_VECTOR(31 DOWNTO 0);
            m_axis_sum_tvalid  : OUT STD_LOGIC;
            m_axis_sum_tready  : IN  STD_LOGIC;
            m_axis_sum_tdata   : OUT STD_LOGIC_VECTOR(31 DOWNTO 0)
        );
    end component;

begin
    swa: sliding_window_adder
        generic map (
            WINDOW_SIZE => WINDOW_SIZE
        )
        port map (
            aclk               => aclk,
            s_axis_val_tvalid  => s_axis_val_tvalid,
            s_axis_val_tready  => s_axis_val_tready,
            s_axis_val_tdata   => s_axis_val_tdata,
            m_axis_sum_tvalid  => m_axis_sum_tvalid,
            m_axis_sum_tready  => m_axis_sum_tready,
            m_axis_sum_tdata   => m_axis_sum_tdata
        );

    clk_process : process
    begin
        aclk <= '0';
        wait for 5 ns;
        aclk <= '1';
        wait for 5 ns;
    end process;

    process begin
        s_axis_val_tvalid <= '0';
        wait for 5 ns;
        
        for i in 0 to 9 loop
            s_axis_val_tdata <= std_logic_vector(to_unsigned(i * 10, 32));
            s_axis_val_tvalid <= '1';
            wait until s_axis_val_tready = '1' and rising_edge(aclk);
            s_axis_val_tvalid <= '0';
            wait for 5 ns;
        end loop;

        wait;
    end process;
end test;
