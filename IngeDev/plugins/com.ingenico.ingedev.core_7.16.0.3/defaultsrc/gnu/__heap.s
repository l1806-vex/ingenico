@ ApplicationHeap initialization

	.code 32

	.section Heap,"aw"

	.global ApplicationHeap
	.lcomm  ApplicationHeap, HEAPSIZE

	.end
