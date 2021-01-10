-include .vscode/avr.properties.mk

ifeq ($(AVR.source.compiler),$(notdir $(AVR.source.compiler)))
A.compiler.dir =
else
A.compiler.dir = $(dir $(AVR.source.compiler))
endif
A.libraries = $(addprefix -I,$(wildcard $(AVR.source.libraries:=/.) $(AVR.source.libraries:=/*/.) $(AVR.source.libraries:=/*/*/.)))
A.output.dir = .vscode/avr.build
A.elf = $(A.output.dir)/output.elf
A.list = $(A.output.dir)/output.lst
A.src = $(call F.dep,$(sort $(wildcard *.c) $(wildcard *.cpp) $(wildcard */*.c) $(wildcard */*.cpp) $(wildcard */*/*.c) $(wildcard */*/*.cpp)))
A.obj = $(addprefix $(A.output.dir)/obj/,$(addsuffix .o,$(basename $(A.src))))

F.dep.base = $(basename $1 $(filter %.h %.hpp,$(shell $(E.get.dep) $1)))
F.dep.1lvl = $(sort $(wildcard $(addsuffix .cpp,$(call F.dep.base,$1))) $(wildcard $(addsuffix .c,$(call F.dep.base,$1))))
F.dep = $(if $(filter-out '$1','$(call F.dep.1lvl,$1)'),$(call F.dep,$(call F.dep.1lvl,$1)),$1)

E.compiler = $(AVR.source.compiler) -DF_CPU=$(AVR.device.frequency) -mmcu=$(AVR.device.type) -pipe $(A.libraries)
E.get.dep = $(E.compiler) -MM
E.compile = $(E.compiler) -std=c++14 -g -Os -Wall -Wextra -pedantic -c -fpermissive -fno-exceptions -ffunction-sections -fdata-sections -fno-threadsafe-statics -MMD -flto
E.link = $(E.compiler) -Wall -Wextra -Os -g -flto -fuse-linker-plugin -Wl,--gc-sections -lm
E.make.list = $(A.compiler.dir)avr-objdump --disassemble --source --line-numbers --demangle
E.get.size = $(A.compiler.dir)avr-size -A

.PHONY : clean build scan

build : $(A.list)
	@$(E.get.size) $(A.elf)

clean :
	@$(RM) -r $(A.output.dir)

scan :
	$(info Found source files)
	$(info )
	$(foreach s,$(A.src),$(info $(realpath $(s))))
	$(info )

-include $(A.obj:.o=.d)

$(A.list) : $(A.elf)
	@mkdir -p $(@D)
	$(info ===== Making $@)
	@$(E.make.list) $^ > $@
	$(info )

$(A.elf) : $(A.obj)
	@mkdir -p $(@D)
	$(info ===== Making $@)
	@$(E.link) $^ -o $@
	$(info )

$(A.output.dir)/obj/%.o : %.c
	@mkdir -p $(@D)
	$(info ===== Making $@)
	@$(E.compile) $< -o $@
	$(info )

$(A.output.dir)/obj/%.o : %.cpp
	@mkdir -p $(@D)
	$(info ===== Making $@)
	@$(E.compile) $< -o $@
	$(info )