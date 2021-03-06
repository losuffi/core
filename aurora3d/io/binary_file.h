#pragma once

#include<string>
#include<module.h>
#include<io/serialize.h>
#include<io/logger.h>

a3d_namespace_io_start

class binary_reader :public reader
{
private:
	ptr::size_t  size = 0;
	std::string  name{};
	uint32       check_sum = 0;
	FILE*        handle = nullptr;
public:

	virtual ~binary_reader() { if (is_opened()) close(); }

	CCDK_FORCEINLINE binary_reader() = default;
	CCDK_FORCEINLINE binary_reader(const std::string& file){ open(file); }
	
	CCDK_FORCEINLINE void close() { if (is_opened()) fclose(handle); }
	
	CCDK_FORCEINLINE bool open(std::string const& filename) {
		if (is_opened()) close();
		return open_impl(filename);
	}

	CCDK_FORCEINLINE virtual bool is_opened() override { return nullptr != handle; }
	
	virtual bool is_end() override { return pos() >= size;  }

	virtual ptr::size_t read(uint8* buf, ptr::size_t size) override {

	}
	virtual bool skip_from_begin(ptr::size_t n) override {

	}
	virtual bool skip_from_cur(ptr::size_t n) override {

	}
	virtual bool skip_from_end(ptr::size_t n) override {

	}

private:

	bool open_impl(std::string const& filename) {
		a3d_assert(!filename.empty());
		std::string path = PathHelper::UnixStylePath(filename);

		if (nullptr == (handle = fopen(path.c_str(), "rb")))
		{
			A3D_WARNING("file " + path + " open failed, please ensure file name is correct.");
			return false;
		}
		fseek(handle, 0, SEEK_END);
		ptr::size_t tmpsz = ftell(handle);
		fseek(handle, 0, SEEK_SET);
		if (0 == tmpsz)
		{
			close();
			A3D_WARNING("file " + path + " is empty");
			return false;
		}

		name = path;
		size = tmpsz;
		return true;
	}

};

class binary_writer : public writer
{
private:
	std::string filename{};
	FILE*       handle = nullptr;
public:
	CCDK_FORCEINLINE binary_writer() = default;
	CCDK_FORCEINLINE binary_writer(const std::string& file,
		Mode mode = Mode::Replace){
		open(file, mode); 
	}
	virtual ~binary_writer() override { close(); }
	virtual bool is_opened() override { return nullptr != handle; }
	virtual bool close() override { if (is_opened()) fclose(handle); }
	virtual bool open(const std::string& fileName, Mode mode = Mode::Replace) override {
		static constexpr char* kWriteMode[2] = { "rb", "r+b" };
		a3d_assert(!fileName.empty());
		if (is_opened()) {
			A3D_WARNING("file " + filename + " already opened, reopen "+fileName+" will close it.");
			close();
		}
		std::string& path = PathHelper::UnixStylePath(fileName);
		if (nullptr == (handle = fopen(path.c_str(), kWriteMode[uint32(mode)]))) {
			A3D_WARNING("file " + path + " open failed, please ensure file name is correct.");
			return false;
		}
		filename = fileName;
		return true;
	}
	virtual ptr::size_t write(const uint8* data, ptr::size_t size) override {
		return fwrite(data, size, 1, handle);
	}
	virtual bool WritedEnd() override { return GetWritedSize() >= 0x7ffffffe; }
};

a3d_namespace_io_end