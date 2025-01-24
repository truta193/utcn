library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use IEEE.NUMERIC_STD.ALL;

entity memory_module is
    port (
        CLK       : in std_logic;
        A         : in std_logic_vector(27 downto 0);  -- 28-bit address
        D         : inout std_logic_vector(15 downto 0);
        RD_n      : in std_logic;
        WR_n      : in std_logic;
        Refresh_n : in std_logic;
        BHE_n     : in std_logic;
        Ready     : out std_logic
    );
end memory_module;

architecture structural of memory_module is
    component memory_submodule
        port (
            A      : in std_logic_vector(9 downto 0);
            D      : inout std_logic_vector(15 downto 0);
            CAS_n  : in std_logic;
            RAS_n  : in std_logic;
            WR_n   : in std_logic;
            BHE_n  : in std_logic;
            A0     : in std_logic
        );
    end component;

    component control_unit
        port (
            CLK       : in std_logic;
            RD_n      : in std_logic;
            WR_n      : in std_logic;
            Refresh_n : in std_logic;
            Enable    : in std_logic;
            AddrSel   : out std_logic;
            RAS_n     : out std_logic;
            CAS_n     : out std_logic;
            Ready     : out std_logic
        );
    end component;

    signal enable : std_logic;
    signal addr_sel : std_logic;
    signal ras_n, cas_n : std_logic;
    signal cas_n_array : std_logic_vector(7 downto 0);
    signal muxed_addr : std_logic_vector(9 downto 0);
begin
    -- Address multiplexing
    muxed_addr <= A(19 downto 10) when addr_sel = '1' else A(9 downto 0);

    -- Decoder for module selection (D0.0000H)
    enable <= '1' when A(27 downto 24) = "1101" else '0';  -- D0h

    -- Control unit
    ctrl_unit: control_unit
    port map (
        CLK       => CLK,
        RD_n      => RD_n,
        WR_n      => WR_n,
        Refresh_n => Refresh_n,
        Enable    => enable,
        AddrSel   => addr_sel,
        RAS_n     => ras_n,
        CAS_n     => cas_n,
        Ready     => Ready
    );

    -- Generate CAS signals for each submodule
    process(cas_n, A)
    begin
        cas_n_array <= (others => '1');
        if cas_n = '0' then
            cas_n_array(to_integer(unsigned(A(22 downto 20)))) <= '0';
        end if;
    end process;

    -- Generate 8 submodules (16MB total)
    gen_submodules: for i in 0 to 7 generate
        submod: memory_submodule
        port map (
            A      => muxed_addr,
            D      => D,
            CAS_n  => cas_n_array(i),
            RAS_n  => ras_n,
            WR_n   => WR_n,
            BHE_n  => BHE_n,
            A0     => A(0)
        );
    end generate;
end structural;