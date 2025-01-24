library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use IEEE.NUMERIC_STD.ALL;

entity tb_memory is
end tb_memory;

architecture behavioral of tb_memory is
    -- Component declaration
    component memory_module
        port (
            CLK       : in std_logic;
            A         : in std_logic_vector(27 downto 0);
            D         : inout std_logic_vector(15 downto 0);
            RD_n      : in std_logic;
            WR_n      : in std_logic;
            Refresh_n : in std_logic;
            BHE_n     : in std_logic;
            Ready     : out std_logic
        );
    end component;

    -- Clock period definition
    constant CLK_PERIOD : time := 10 ns;

    -- Test signals
    signal clk       : std_logic := '0';
    signal addr      : std_logic_vector(27 downto 0) := (others => '0');
    signal data      : std_logic_vector(15 downto 0) := (others => 'Z');
    signal rd_n      : std_logic := '1';
    signal wr_n      : std_logic := '1';
    signal refresh_n : std_logic := '1';
    signal bhe_n     : std_logic := '1';
    signal ready     : std_logic;

    -- Helper procedures
    procedure write_word(
        signal addr_sig   : out std_logic_vector(27 downto 0);
        signal data_sig   : out std_logic_vector(15 downto 0);
        signal wr_sig     : out std_logic;
        signal ready_sig  : in  std_logic;
        constant address  : in  std_logic_vector(27 downto 0);
        constant value    : in  std_logic_vector(15 downto 0)) is
    begin
        -- Set up address and data
        addr_sig <= address;
        wait for CLK_PERIOD;
        -- Wait for RAS cycle
        data_sig <= value;
        wr_sig <= '0';
        -- Wait for ready to indicate operation complete
        wait until ready_sig = '0';
        wait until ready_sig = '1';
        -- De-assert write
        wr_sig <= '1';
        data_sig <= (others => 'Z');
        wait for CLK_PERIOD;
    end procedure;

    procedure read_word(
        signal addr_sig   : out std_logic_vector(27 downto 0);
        signal rd_sig     : out std_logic;
        signal ready_sig  : in  std_logic;
        constant address  : in  std_logic_vector(27 downto 0)) is
    begin
        -- Set up address
        addr_sig <= address;
        wait for CLK_PERIOD;
        -- Assert read
        rd_sig <= '0';
        -- Wait for ready to indicate operation complete
        wait until ready_sig = '0';
        wait until ready_sig = '1';
        -- De-assert read
        rd_sig <= '1';
        wait for CLK_PERIOD;
    end procedure;

begin
    -- Instantiate the Unit Under Test (UUT)
    uut: memory_module
    port map (
        CLK       => clk,
        A         => addr,
        D         => data,
        RD_n      => rd_n,
        WR_n      => wr_n,
        Refresh_n => refresh_n,
        BHE_n     => bhe_n,
        Ready     => ready
    );

    -- Clock process
    clk_process: process
    begin
        clk <= '0';
        wait for CLK_PERIOD/2;
        clk <= '1';
        wait for CLK_PERIOD/2;
    end process;

    -- Stimulus process
    stim_proc: process
        variable test_addr : std_logic_vector(27 downto 0);
        variable test_data : std_logic_vector(15 downto 0);
    begin
        -- Wait 100ns for global reset
        wait for 100 ns;

        -- Test 1: Write and read to valid address (D0.0000H)
        report "Test 1: Write and read to valid address";
        test_addr := x"D000000"; -- 28-bit address
        test_data := x"1234";
        write_word(addr, data, wr_n, ready, test_addr, test_data);
        wait for CLK_PERIOD*2;
        read_word(addr, rd_n, ready, test_addr);

        -- Test 2: Test byte access (low byte)
        report "Test 2: Test byte access (low byte)";
        test_addr := x"D000002"; -- 28-bit address
        test_data := x"00AB";
        bhe_n <= '1';  -- Disable high byte
        write_word(addr, data, wr_n, ready, test_addr, test_data);
        wait for CLK_PERIOD*2;
        read_word(addr, rd_n, ready, test_addr);

        -- Test 3: Test byte access (high byte)
        report "Test 3: Test byte access (high byte)";
        test_addr := x"D000004"; -- 28-bit address
        test_data := x"CD00";
        bhe_n <= '0';  -- Enable high byte
        write_word(addr, data, wr_n, ready, test_addr, test_data);
        wait for CLK_PERIOD*2;
        read_word(addr, rd_n, ready, test_addr);

        -- Test 4: Test refresh cycle
        report "Test 4: Test refresh cycle";
        refresh_n <= '0';
        wait for CLK_PERIOD*4;
        refresh_n <= '1';

        -- Test 5: Access invalid address (outside D0.0000H-D7.FFFFH range)
        report "Test 5: Access invalid address";
        test_addr := x"E000000"; -- 28-bit address
        test_data := x"FFFF";
        write_word(addr, data, wr_n, ready, test_addr, test_data);
        wait for CLK_PERIOD*2;
        read_word(addr, rd_n, ready, test_addr);

        -- Test 6: Rapid read/write sequence to test RAS/CAS timing
        report "Test 6: Rapid read/write sequence";
        for i in 0 to 3 loop
            -- Create base address D000000 using concatenation and add offset
            test_addr := "1101" & std_logic_vector(to_unsigned(0, 24)); -- D000000
            test_addr := std_logic_vector(unsigned(test_addr) + (i*2));
            test_data := std_logic_vector(to_unsigned(i*4369, 16)); -- 0x1111, 0x2222, etc.
            write_word(addr, data, wr_n, ready, test_addr, test_data);
            wait for CLK_PERIOD;
            read_word(addr, rd_n, ready, test_addr);
        end loop;

        -- Test 7: Test auto-refresh timing
        report "Test 7: Wait for auto-refresh";
        wait for 2 ms;  -- Wait for auto-refresh cycle
        
        -- End simulation
        report "Simulation completed successfully";
        wait;
    end process;

    -- Monitor process for refresh operations
    monitor_proc: process
    begin
        wait until rising_edge(clk);
        if refresh_n = '0' then
            report "Refresh cycle detected";
        end if;
    end process;

end behavioral;