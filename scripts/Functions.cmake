
macro(append_unless listVar item condVar)
	if (NOT ${${condVar}})
		list(APPEND ${listVar} ${item})
	endif()
endmacro()


