// Code generated by bpf2go; DO NOT EDIT.
//go:build 386 || amd64 || arm || arm64 || loong64 || mips64le || mipsle || ppc64le || riscv64

package main

import (
	"bytes"
	_ "embed"
	"fmt"
	"io"

	"github.com/cilium/ebpf"
)

// loadPass returns the embedded CollectionSpec for pass.
func loadPass() (*ebpf.CollectionSpec, error) {
	reader := bytes.NewReader(_PassBytes)
	spec, err := ebpf.LoadCollectionSpecFromReader(reader)
	if err != nil {
		return nil, fmt.Errorf("can't load pass: %w", err)
	}

	return spec, err
}

// loadPassObjects loads pass and converts it into a struct.
//
// The following types are suitable as obj argument:
//
//	*passObjects
//	*passPrograms
//	*passMaps
//
// See ebpf.CollectionSpec.LoadAndAssign documentation for details.
func loadPassObjects(obj interface{}, opts *ebpf.CollectionOptions) error {
	spec, err := loadPass()
	if err != nil {
		return err
	}

	return spec.LoadAndAssign(obj, opts)
}

// passSpecs contains maps and programs before they are loaded into the kernel.
//
// It can be passed ebpf.CollectionSpec.Assign.
type passSpecs struct {
	passProgramSpecs
	passMapSpecs
}

// passSpecs contains programs before they are loaded into the kernel.
//
// It can be passed ebpf.CollectionSpec.Assign.
type passProgramSpecs struct {
	XdpMain *ebpf.ProgramSpec `ebpf:"xdp_main"`
}

// passMapSpecs contains maps before they are loaded into the kernel.
//
// It can be passed ebpf.CollectionSpec.Assign.
type passMapSpecs struct {
}

// passObjects contains all objects after they have been loaded into the kernel.
//
// It can be passed to loadPassObjects or ebpf.CollectionSpec.LoadAndAssign.
type passObjects struct {
	passPrograms
	passMaps
}

func (o *passObjects) Close() error {
	return _PassClose(
		&o.passPrograms,
		&o.passMaps,
	)
}

// passMaps contains all maps after they have been loaded into the kernel.
//
// It can be passed to loadPassObjects or ebpf.CollectionSpec.LoadAndAssign.
type passMaps struct {
}

func (m *passMaps) Close() error {
	return _PassClose()
}

// passPrograms contains all programs after they have been loaded into the kernel.
//
// It can be passed to loadPassObjects or ebpf.CollectionSpec.LoadAndAssign.
type passPrograms struct {
	XdpMain *ebpf.Program `ebpf:"xdp_main"`
}

func (p *passPrograms) Close() error {
	return _PassClose(
		p.XdpMain,
	)
}

func _PassClose(closers ...io.Closer) error {
	for _, closer := range closers {
		if err := closer.Close(); err != nil {
			return err
		}
	}
	return nil
}

// Do not access this directly.
//
//go:embed pass_bpfel.o
var _PassBytes []byte
