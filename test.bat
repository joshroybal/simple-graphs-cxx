@echo on
driver %1
dot -Tsvg graph.gv > graph.svg
