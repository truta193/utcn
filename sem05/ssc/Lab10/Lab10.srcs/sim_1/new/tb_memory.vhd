library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use IEEE.NUMERIC_STD.ALL;

entity tb_memory is
end tb_memory;

architecture behavioral of tb_memory is
    component memory_module
        port (
            CLK    : in std_logic;
            A      : in std_logic_vector(23 downto 0);
            D      : inout std_logic_vector(15 downto 0);
            RD_n   : in std_logic;
            WR_n   : in std_logic;
            BHE_n  : in std_logic;
            READY  : out std_logic
        );
    end component;

    constant CLK_PERIOD : time := 10 ns;

    -- Test signals
    signal clk         : std_logic := '0';
    signal addr        : std_logic_vector(23 downto 0) := (others => '0');
    signal data        : std_logic_vector(15 downto 0) := (others => 'Z');
    signal rd_n        : std_logic := '1';
    signal wr_n        : std_logic := '1';
    signal bhe_n       : std_logic := '1';
    signal ready       : std_logic;

    procedure write_word(
        signal addr_sig : out std_logic_vector(23 downto 0);
        signal data_sig : out std_logic_vector(15 downto 0);
        signal wr_sig   : out std_logic;
        signal ready_sig: in  std_logic;
        constant address: in  std_logic_vector(23 downto 0);
        constant value  : in  std_logic_vector(15 downto 0)) is
    begin
        addr_sig <= address;
        data_sig <= value;
        wait for CLK_PERIOD;
        wr_sig <= '0';
        wait until ready_sig = '0';
        wait until ready_sig = '1';
        wr_sig <= '1';
        data_sig <= (others => 'Z');
        wait for CLK_PERIOD;
    end procedure;

    procedure read_word(
        signal addr_sig : out std_logic_vector(23 downto 0);
        signal rd_sig   : out std_logic;
        signal ready_sig: in  std_logic;
        constant address: in  std_logic_vector(23 downto 0)) is
    begin
        addr_sig <= address;
        wait for CLK_PERIOD;
        rd_sig <= '0';
        wait until ready_sig = '0';
        wait until ready_sig = '1';
        rd_sig <= '1';
        wait for CLK_PERIOD;
    end procedure;

begin
    mm: memory_module
    port map (
        CLK    => clk,
        A      => addr,
        D      => data,
        RD_n   => rd_n,
        WR_n   => wr_n,
        BHE_n  => bhe_n,
        READY  => ready
    );

    clk_process: process
    begin
        clk <= '0';
        wait for CLK_PERIOD/2;
        clk <= '1';
        wait for CLK_PERIOD/2;
    end process;

    process
        variable test_addr : std_logic_vector(23 downto 0);
        variable test_data : std_logic_vector(15 downto 0);
    begin
        wait for 100 ns;

        -- Test 1: Write and read to/from C0.0000H
        test_addr := x"C00000";
        test_data := x"1234";
        write_word(addr, data, wr_n, ready, test_addr, test_data);
        wait for CLK_PERIOD*2;
        read_word(addr, rd_n, ready, test_addr);

        -- Test 2: Write and read to/from C1.0000H
        test_addr := x"C10000";
        test_data := x"5678";
        write_word(addr, data, wr_n, ready, test_addr, test_data);
        wait for CLK_PERIOD*2;
        read_word(addr, rd_n, ready, test_addr);

        -- Test 3: Test byte access (low byte)
        test_addr := x"C20000";
        test_data := x"00AB";
        bhe_n <= '1';  -- Disable high byte
        write_word(addr, data, wr_n, ready, test_addr, test_data);
        wait for CLK_PERIOD*2;
        read_word(addr, rd_n, ready, test_addr);

        -- Test 4: Test byte access (high byte)
        test_addr := x"C20002";
        test_data := x"CD00";
        bhe_n <= '0';  -- Enable high byte
        write_word(addr, data, wr_n, ready, test_addr, test_data);
        wait for CLK_PERIOD*2;
        read_word(addr, rd_n, ready, test_addr);

        -- Test 5: Access invalid address (outside C0.0000H-C7.FFFFH range)
        test_addr := x"D00000";
        test_data := x"FFFF";
        bhe_n <= '0';
        write_word(addr, data, wr_n, ready, test_addr, test_data);
        wait for CLK_PERIOD*2;
        read_word(addr, rd_n, ready, test_addr);

        wait;
    end process;

end behavioral;