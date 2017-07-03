#ifndef STATE_H
#define STATE_H

namespace core
{
    struct MachineState
    {
        std::vector<uint32_t> mem;
        std::array<uint32_t, 8> regs;
        uint32_t pc;
        uint32_t psr;
    };

    typedef enum {
          STATE_CHANGE_REG
        , STATE_CHANGE_PSR
        , STATE_CHANGE_PC
        , STATE_CHANGE_MEM
    } StateChangeType;

    class IStateChange
    {
    public:
        StateChangeType type;

        IStateChange(StateChangeType type) : type(type) {}
        virtual void updateState(MachineState & state) const = 0;
        virtual std::string getOutputString(MachineState const & state) const = 0;
    };

    class RegStateChange : public IStateChange
    {
    public:
        RegStateChange(uint32_t reg, uint32_t value) : IStateChange(STATE_CHANGE_REG), reg(reg), value(value) {}
        virtual void updateState(MachineState & state) const override { state.regs[reg] = value; }
        virtual std::string getOutputString(MachineState const & state) const override { return toString("R%d: 0x%0.4x => 0x%0.4x", reg, state.regs[reg], value); }
    private:
        uint32_t reg;
        uint32_t value;
    };

    class PSRStateChange : public IStateChange
    {
    public:
        uint32_t value;

        PSRStateChange(uint32_t value) : IStateChange(STATE_CHANGE_PSR), value(value) {}
        virtual void updateState(MachineState & state) const override { state.psr = value; }
        virtual std::string getOutputString(MachineState const & state) const override { return toString("PSR: 0x%0.4x => 0x%0.4x", state.psr, value); }
    };

    class PCStateChange : public IStateChange
    {
    public:
        uint32_t value;

        PCStateChange(uint32_t value) : IStateChange(STATE_CHANGE_PC), value(value) {}
        virtual void updateState(MachineState & state) const override { state.pc = value; }
        virtual std::string getOutputString(MachineState const & state) const override { return toString("PC: 0x%0.4x => 0x%0.4x", state.pc, value); }
    };

    class MemStateChange : public IStateChange
    {
    public:
        uint32_t addr;
        uint32_t value;

        MemStateChange(uint32_t addr, uint32_t value) : IStateChange(STATE_CHANGE_MEM), addr(addr), value(value) {}
        virtual void updateState(MachineState & state) const override { state.mem[addr] = value; }
        virtual std::string getOutputString(MachineState const & state) const override { return toString("MEM[0x%0.4x]: 0x%0.4x => 0x%0.4x", addr, state.mem[addr], value); }
    };
};

#endif
