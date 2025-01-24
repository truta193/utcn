library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use IEEE.NUMERIC_STD.ALL;

entity memory_module is
    port (
        CLK    : in std_logic;
        A      : in std_logic_vector(23 downto 0);
        D      : inout std_logic_vector(15 downto 0);
        RD_n   : in std_logic;
        WR_n   : in std_logic;
        BHE_n  : in std_logic;
        READY  : out std_logic
    );
end memory_module;

architecture structural of memory_module is
    component decoder
        port (
            A      : in std_logic_vector(23 downto 17);
            RD_n   : in std_logic;
            WR_n   : in std_logic;
            Sel_n  : out std_logic_vector(7 downto 0);
            Enable : out std_logic
        );
    end component;

    component memory_submodule
        port (
            A      : in std_logic_vector(15 downto 0);
            D      : inout std_logic_vector(15 downto 0);
            Sel_n  : in std_logic;
            WR_n   : in std_logic;
            BHE_n  : in std_logic;
            A0     : in std_logic
        );
    end component;

    component control_unit
        port (
            CLK      : in std_logic;
            RD_n     : in std_logic;
            WR_n     : in std_logic;
            Enable   : in std_logic;
            READY    : out std_logic;
            MEM_RD_n : out std_logic;
            MEM_WR_n : out std_logic
        );
    end component;

    signal sel_n : std_logic_vector(7 downto 0);
    signal enable : std_logic;
    signal mem_rd_n, mem_wr_n : std_logic;
begin
    -- Decoder instance
    decoder_inst: decoder
    port map (
        A      => A(23 downto 17),
        RD_n   => RD_n,
        WR_n   => WR_n,
        Sel_n  => sel_n,
        Enable => enable
    );
    
    -- Generate 8 sub-modules (512k total)
    gen_submodules: for i in 0 to 7 generate
        submod: memory_submodule
        port map (
            A      => A(16 downto 1),
            D      => D,
            Sel_n  => sel_n(i),
            WR_n   => WR_n,
            BHE_n  => BHE_n,
            A0     => A(0)
        );
    end generate;

    -- Control unit instance
    control_unit_inst: control_unit
    port map (
        CLK      => CLK,
        RD_n     => RD_n,
        WR_n     => WR_n,
        Enable   => enable,
        READY    => READY,
        MEM_RD_n => mem_rd_n,
        MEM_WR_n => mem_wr_n
    );
end structural;
