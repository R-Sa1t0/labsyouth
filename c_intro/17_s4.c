#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "17_s3_def.h"

static int cmp_ext_asc(const void* va, const void* vb) {
	const EXT *a=va, *b=vb;
	return strcmp(a->ext, b->ext);
}
static int cmp_ext_desc(const void* va, const void* vb) {
	return cmp_ext_asc(vb, va);
}

static int cmp_count_asc(const void* va, const void* vb) {
	const EXT *a=va, *b=vb;
	return a->count-b->count;
}
static int cmp_count_desc(const void* va, const void* vb) {
	return cmp_count_asc(vb, va);
}

static int cmp_total_asc(const void* va, const void* vb) {
	const EXT *a=va, *b=vb;
	return a->size-b->size;
}
static int cmp_total_desc(const void* va, const void* vb) {
	return cmp_total_asc(vb, va);
}

static int cmp_average_asc(const void* va, const void* vb) {
	const EXT *a=va, *b=vb;
	return a->size/a->count-b->size/b->count;
}
static int cmp_average_desc(const void* va, const void* vb) {
	return cmp_average_asc(vb, va);
}

int main(int argc, char* argv[]) {
	struct {
		char str[3];
		int (*cmp)(const void*, const void*);
	} opt[]={
		{"ea", cmp_ext_asc}, {"ed", cmp_ext_desc}, 
		{"ca", cmp_count_asc}, {"cd", cmp_count_desc}, 
		{"ta", cmp_total_asc}, {"td", cmp_total_desc}, 
		{"aa", cmp_average_asc}, {"ad", cmp_average_desc}
	};
	int opt_i=0, opt_n=sizeof opt/sizeof opt[0];
	if (argc<2) {
		printf("usage: %s [", argv[0]);
		for (int i=0; i<opt_n-1; i++) printf("-%s|", opt[i].str);
		printf("%s] path\n", opt[opt_n-1].str);
		return 1;
	}
	for (int i=1; i<argc; i++) {
		if (argv[i][0]=='-') {
			for (opt_i=0; opt_i<opt_n && 
				strcmp(opt[opt_i].str, argv[i]+1); opt_i++);
			if (opt_i==opt_n) {
				printf("unknown option: %s\n", argv[i]);
				return 1;
			}
		} else {
			ext_begin();
			ext_find_files(argv[i]);
			qsort(ext_p, ext_n, sizeof(EXT), opt[opt_i].cmp);
			ext_report();
			ext_end();
		}
	}
}
