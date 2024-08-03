package handler

import (
	"fmt"
	"net/http"
	"stor/pkg/domain"
	"stor/pkg/repository"

	"github.com/gin-gonic/gin"
)

var ErrorBind = domain.Error{Error: "BindJson Error"}

func (h *Handler) HandlerWriteFile(c *gin.Context) {
	var (
		data domain.WriteData
	)
	if err := c.BindJSON(&data); err != nil {
		c.JSON(http.StatusBadRequest, ErrorBind)
		return
	}
	fmt.Println(data)
	h.Service.WriteFile(data)
}

func (h *Handler) HandlerReadFile(c *gin.Context) {
	var (
		data domain.FileData
	)

	if err := c.BindJSON(&data); err != nil {
		c.JSON(http.StatusBadRequest, ErrorBind)
		return
	}
	fmt.Println(data)
	byte_data := h.Service.ReadFile(data)
	c.JSON(http.StatusOK, byte_data)
}

func (h *Handler) HandlerCreateFile(c *gin.Context) {
	var (
		data domain.FileData
	)

	if err := c.BindJSON(&data); err != nil {
		fmt.Errorf("%s", "%w", "pkg.handler.cloude", err)
		c.JSON(http.StatusBadRequest, ErrorBind)
		return
	}
	fmt.Println(data)
	h.Service.NewFile(data)
}

func (h *Handler) HandlerCreateDir(c *gin.Context) {
	var (
		data domain.DirData
	)

	if err := c.BindJSON(&data); err != nil {

		c.JSON(http.StatusBadRequest, ErrorBind)
		return
	}
	fmt.Println(data)
	if !h.Service.NewDir(data) {
		c.JSON(http.StatusBadRequest, nil)
		return
	}

	c.AbortWithStatus(http.StatusOK)
}

func (h *Handler) HandlerDeleteFile(c *gin.Context) {
	var (
		data domain.FileData
	)

	if err := c.BindJSON(&data); err != nil {
		c.JSON(http.StatusBadRequest, domain.Error{Error: "Bind FileError {delete file}"})
		return
	}
	fmt.Println(data)
	status := h.Service.DeleteFile(data)
	if !status {
		c.JSON(http.StatusBadRequest, domain.Error{Error: "Delete FileError"})
		return
	}
	c.JSON(http.StatusOK, nil)
}

func (h *Handler) HandlerDeleteDir(c *gin.Context) {
	var (
		data domain.DirData
	)

	if err := c.BindJSON(&data); err != nil {
		c.JSON(http.StatusBadRequest, ErrorBind)
		return
	}
	fmt.Println(data)
	status := h.Service.DeleteDir(data)
	if !status {
		c.JSON(http.StatusBadRequest, domain.Error{Error: "Delete DirError"})
		return
	}
	c.JSON(http.StatusOK, nil)
}

func (h *Handler) HandlerIsFile(c *gin.Context) {
	var (
		data domain.FileData
	)

	if err := c.BindJSON(&data); err != nil {
		fmt.Errorf("%s", "%w", "pkg.handler.cloude", err)
		c.JSON(http.StatusBadRequest, ErrorBind)
		return
	}
	fmt.Println(data)
	status := h.Service.IsFile(data)
	c.JSON(http.StatusOK, domain.IsExists{IsExists: status})
}

func (h *Handler) HandlerIsDir(c *gin.Context) {
	var (
		data domain.DirData
	)

	if err := c.BindJSON(&data); err != nil {
		fmt.Errorf("%s", "%w", "pkg.handler.cloude", err)
		c.JSON(http.StatusBadRequest, ErrorBind)
		return
	}
	fmt.Println(data)
	status := h.Service.IsDir(data)
	c.JSON(http.StatusOK, domain.IsExists{IsExists: status})
}

func (h *Handler) HandlerDirNameAll(c *gin.Context) {
	var (
		data domain.Location
	)

	if err := c.BindJSON(&data); err != nil {
		fmt.Errorf("%s", "%w", "pkg.handler.cloude", err)
		c.JSON(http.StatusBadRequest, ErrorBind)
		return
	}
	fmt.Println(data)
	status := h.Service.DirNameAll(data.Path)
	c.JSON(http.StatusOK, repository.ResponeData{DataMass: status})
}

func (h *Handler) HandlerFileNameAll(c *gin.Context) {
	var (
		data domain.Location
	)

	if err := c.BindJSON(&data); err != nil {
		fmt.Errorf("%s", "%w", "pkg.handler.cloude", err)
		c.JSON(http.StatusBadRequest, ErrorBind)
		return
	}
	fmt.Println(data)
	status := h.Service.FileNameAll(data.Path)
	c.JSON(http.StatusOK, repository.ResponeData{DataMass: status})
}
