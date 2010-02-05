# SICemu - SIC architecture interpreter and emulator
# 
#      Code section starts at 0x00000000
# Variables section starts at 0xF0000000 
#

# Regexes definitions for source code interpretation,
REGEX_SPACE         = "\\s*"
REGEX_HEXADDR       = "0x[a-fA-F0-9]{1,8}"
REGEX_DECIMALADDR   = "\\d{1,8}"
REGEX_VARIABLE      = "[a-zA-Z][A-Za-z0-9]*"
REGEX_ADDRESS       = "(#{REGEX_HEXADDR})|(#{REGEX_DECIMALADDR})"
REGEX_COMMENT       = "\\s*#.*"
REGEX_OPERAND       = "(#{REGEX_ADDRESS})|(#{REGEX_VARIABLE})"
REGEX_INSTRUCTION   = "\\s*SBN\\s+(#{REGEX_OPERAND})\\s*,\\s*(#{REGEX_OPERAND})\\s*,\\s*(#{REGEX_OPERAND})" +
                      "(#{REGEX_COMMENT}){0,1}" 
REGEX_SRCLINE       = "^((#{REGEX_INSTRUCTION})|(#{REGEX_COMMENT})|(#{REGEX_SPACE}))$"

class SICemu

    def initialize(debug=false)
        @debug = debug
        @mem = {}
        @mem.default = 0
        @addr = 0
        @vars = {}
        @next_var_addr = 0xF0000000
        @filename = ""
    end
    
	# load an assembly file (.sic) to be interpreted.    
    def load_file(filename)
        
        regex_srcline = Regexp.new(REGEX_SRCLINE)
        
        file = File.open(filename, 'r')
        line_number = 0
        
        file.each_line do |line|
            puts "[#{line_number}] #{line}" if @debug
            
            match = regex_srcline.match(line)
            
            if match == nil
                puts "[!] Invalid source line : #{line_number}"
                return false
            end
            
            sbn_line = match[2]
            a_hex    = match[5]
            a_dec    = match[6]
            a_var    = match[7]
            b_hex    = match[10]
            b_dec    = match[11]
            b_var    = match[12]
            c_hex    = match[15]
            c_dec    = match[16]
            c_var    = match[17]            
            
            if sbn_line
            
                # operand A
                if a_hex
                    a = a_hex.to_i(16)                    
                elsif a_dec
                    a = a_dec.to_i
                else # a is a variable
                    a = get_variable(a_var)
                end
                
                # operand B
                if b_hex
                    b = b_hex.to_i(16)   
                elsif b_dec
                    b = b_dec.to_i
                else # a is a variable
                    b = get_variable(b_var)
                end
                
                # operand C
                if c_hex
                    c = c_hex.to_i(16)   
                elsif c_dec
                    c = c_dec.to_i
                else # a is a variable
                    c = get_variable(c_var)
                end
                
                
                # load instruction
                load_instruction(a,b,c)
                
            end
      
            line_number += 1
        
        end
    end
    
	# load an object file to be executed.
	# Note that the object file format does contain information on
	# variables, so mapping must be done manually via set_var().
    def load_object(filename)
        
        file = File.open(filename, 'r')
        
        while not file.eof
            a,b,c = file.read(12).unpack('N3')
            load_instruction(a, b, c)
        end
    
    end

	# loads an instruction in memory
    def load_instruction(operand_a, operand_b, operand_c)
 
        @mem[@addr]   = operand_a
        @mem[@addr+4] = operand_b
        @mem[@addr+8] = operand_c
        
        puts "A: %08x B: %08x C: %08x " % [@mem[@addr], @mem[@addr+4], @mem[@addr+8]] if @debug
        
        # Increasing memory pointer to next location for load
        @addr += 12
    end
    
    # get the value of variable
	# if the variable does not already exist, a
	# new one is created and initialized to 0.
    def get_variable(name) 
             
        if @vars.has_key?(name)
            
            # the variable already exists
            return @vars[name]
        
        else
            # create a new variable and return it
            addr = @next_var_addr
            set_var(name, addr)
            @next_var_addr += 4
            return addr
        end   
    end
    
	# set the value of a variable.
	# creates the variable if it does not already exist.
    def set_variable(name, value=0)
        
        
        if @vars.has_key?(name)
            
            # the variable already exists
            set_var(name, @vars[name], value)
        
        else
            # create a new variable and return it
            addr = @next_var_addr
            set_var(name, addr, value)
            @next_var_addr += 4
            return addr
            
        end
    end
    
  
    
    # internal method to set a variable at a specific adress, should not
    # be used directly.
    
    def set_var(name, address, value=0)
        
        begin
            if @vars.has_key?(name)
                raise "[!] ERROR: variable %s already exists at address 0x%08x" % [name, @vars[name]]
            elsif @vars.has_value?(address)
                raise "[!] ERROR: address 0x#{address.to_s(16)} already contains a variable."
            end
        end
        
        puts "creating variable #{name} at address 0x#{address.to_s(16)}" if @debug
        
        @vars[name]    = address
        @mem[address]  = value
    end
    
    # dumps the content of variables
    def show_variables()
        puts "[-] Variables:"
        @vars.each_pair do |name,address|
            puts "%s (0x%08x) : %d" % [name, address, @mem[address]]
        end
    end
    
	# dumps the content of memory
    def dump_memory()
        puts @mem
    end
    
	# execute an instruction
    def execute_instruction(trace=false)
    
        addr_a = @addr
        addr_b = @addr+4
        addr_c = @addr+8
    
        a = @mem[addr_a]
        b = @mem[addr_b]
        c = @mem[addr_c]    
       

       
        if a == 0 && b == 0 && c == 0
            raise "EndOfProgram"
        end
       
       if @debug or trace
            vars  = @vars.invert
            var_a = vars.has_key?(a) ? vars[a] : a.to_s
            var_b = vars.has_key?(b) ? vars[b] : b.to_s
            var_c = vars.has_key?(c) ? vars[c] : "0x%08x" % [c]
           
            puts "[0x%08x] SBN %s, %s, %s"  % [@addr,var_a, var_b, var_c]
            show_variables if @debug
        end
        
        # SBN instruction
        #
        # MEM[A] = MEM[A] - MEM[B]
        # if MEM[A] < 0 then PC = PC + C
        #puts "a: 0x%04x b: 0x%04x" % [a, b]
        #puts "MEM[A]: %d MEM[B]: %d" % [@mem[a], @mem[b]]
        
        @mem[a] = @mem[a] - @mem[b]
        a = @mem[a]
        @addr += 12 
        
        if a < 0
            @addr = @addr + c
            puts "[!] jumping to 0x#{@addr.to_s(16)}" if @debug or trace
        end
    
    end
    
	# run the loaded program
    def run(trace=false)
        
        # Setting PC to beginning of program.
        @addr = 0
        
        puts "[-] Executing program" if @debug
        while true
            begin
                execute_instruction(trace)
            rescue RuntimeError
                return
            end
        end
        
    end
end



