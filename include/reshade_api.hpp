/*
 * Copyright (C) 2021 Patrick Mours
 * License: https://github.com/crosire/reshade#license
 */

#pragma once

#include "reshade_api_pipeline.hpp"
#include "reshade_api_resource.hpp"

#ifndef DECLSPEC_NOVTABLE
	#if (_MSC_VER >= 1100) && defined(__cplusplus)
		#define DECLSPEC_NOVTABLE __declspec(novtable)
	#else
		#define DECLSPEC_NOVTABLE
	#endif
#endif

namespace reshade { namespace api
{
	/// <summary>
	/// The underlying render API a device is using, as returned by <see cref="device::get_api"/>.
	/// </summary>
	enum class device_api
	{
		/// <summary>
		/// Direct3D 9
		/// </summary>
		/// <remarks>https://docs.microsoft.com/windows/win32/direct3d9</remarks>
		d3d9 = 0x9000,
		/// <summary>
		/// Direct3D 10
		/// </summary>
		/// <remarks>https://docs.microsoft.com/windows/win32/direct3d10</remarks>
		d3d10 = 0xa000,
		/// <summary>
		/// Direct3D 11
		/// </summary>
		/// <remarks>https://docs.microsoft.com/windows/win32/direct3d11</remarks>
		d3d11 = 0xb000,
		/// <summary>
		/// Direct3D 12
		/// </summary>
		/// <remarks>https://docs.microsoft.com/windows/win32/direct3d12</remarks>
		d3d12 = 0xc000,
		/// <summary>
		/// OpenGL
		/// </summary>
		/// <remarks>https://www.khronos.org/opengl/</remarks>
		opengl = 0x10000,
		/// <summary>
		/// Vulkan
		/// </summary>
		/// <remarks>https://www.khronos.org/vulkan/</remarks>
		vulkan = 0x20000
	};

	/// <summary>
	/// The available features a device may support.
	/// </summary>
	enum class device_caps
	{
		/// <summary>
		/// Specifies whether compute shaders are supported.
		/// If this feature is not present, the "compute_shader" pipeline state must not be used.
		/// </summary>
		compute_shader = 1,
		/// <summary>
		/// Specifies whether geometry shaders are supported.
		/// If this feature is not present, the "geometry_shader" pipeline state must not be used.
		/// </summary>
		geometry_shader,
		/// <summary>
		/// Specifies whether hull and domain shaders are supported.
		/// If this feature is not present, the "hull_shader" and "domain_shader" pipeline state must not be used.
		/// </summary>
		hull_and_domain_shader,
		/// <summary>
		/// Specifies whether blend operations which take two sources are supported.
		/// If this feature is not present, <see cref="blend_factor::src1_color"/>, <see cref="blend_factor::inv_src1_color"/>, <see cref="blend_factor::src1_alpha"/> and <see cref="blend_factor::inv_src1_alpha"/> must not be used.
		/// </summary>
		dual_src_blend,
		/// <summary>
		/// Specifies whether blend state is controlled independently per render target.
		/// If this feature is not present, the blend state settings for all render targets must be identical.
		/// </summary>
		independent_blend,
		/// <summary>
		/// Specifies whether logic operations are available in the blend state.
		/// If this feature is not present, the "logic_op_enable" and "logic_op" fields of <see cref="pipeline_desc"/> are ignored.
		/// </summary>
		logic_op,
		/// <summary>
		/// Specifies whether instancing is supported.
		/// If this feature is not present, the "instances" and "first_instance" parameters to <see cref="command_list::draw"/> and <see cref="command_list::draw_indexed"/> must be 1 and 0.
		/// </summary>
		draw_instanced,
		/// <summary>
		/// Specifies whether indirect draw or dispatch calls are supported.
		/// If this feature is not present, <see cref="command_list::draw_or_dispatch_indirect"/> must not be used.
		/// </summary>
		draw_or_dispatch_indirect,
		/// <summary>
		/// Specifies whether point and wireframe fill modes are supported.
		/// If this feature is not present, <see cref="fill_mode::point"/> and <see cref="fill_mode::wireframe"/> must not be used.
		/// </summary>
		fill_mode_non_solid,
		/// <summary>
		/// Specifies whther more than one viewport is supported.
		/// If this feature is not present, the "first" and "count" parameters to <see cref="command_list::bind_viewports"/> must be 0 and 1.
		/// </summary>
		multi_viewport,
		/// <summary>
		/// Specifies whether partial push constant updates are supported.
		/// If this feature is not present, the "first" parameter to <see cref="command_list::push_constants"/> must be 0 and "count" must cover the entire constant range.
		/// </summary>
		partial_push_constant_updates,
		/// <summary>
		/// Specifies whether partial push descriptor updates are supported.
		/// If this feature is not present, the "first" parameter to <see cref="command_list::push_descriptors"/> must be 0 and "count" must cover the entire descriptor range.
		/// </summary>
		partial_push_descriptor_updates,
		/// <summary>
		/// Specifies whether comparison sampling is supported.
		/// If this feature is not present, the "compare_op" field of <see cref="sampler_desc"/> is ignored.
		/// </summary>
		sampler_compare_op,
		/// <summary>
		/// Specifies whether anisotropic filtering is supported.
		/// If this feature is not present, <see cref="texture_filter::anisotropic"/> must not be used.
		/// </summary>
		sampler_anisotropic_filtering,
		/// <summary>
		/// Specifies whether combined sampler and resource view descriptors are supported.
		/// If this feature is not present, <see cref="descriptor_type::sampler_with_resource_view"/> must not be used.
		/// </summary>
		sampler_with_resource_view,
		/// <summary>
		/// Specifies whether copying between buffers is supported.
		/// If this feature is not present, <see cref="command_list::copy_buffer_region"/> must not be used.
		/// </summary>
		copy_buffer_region,
		/// <summary>
		/// Specifies whether copying between buffers and textures is supported.
		/// If this feature is not present, <see cref="command_list::copy_buffer_to_texture"/> and <see cref="command_list::copy_texture_to_buffer"/> must not be used.
		/// </summary>
		copy_buffer_to_texture,
		/// <summary>
		/// Specifies whether blitting between resources is supported.
		/// If this feature is not present, the "src_box" and "dst_box" parameters to <see cref="command_list::copy_texture_region"/> must have the same dimensions.
		/// </summary>
		blit,
		/// <summary>
		/// Specifies whether resolving a region of a resource rather than its entirety is supported.
		/// If this feature is not present, the "src_offset", "dst_offset" and "size" parameters to <see cref="command_list::resolve"/> must be <c>nullptr</c>.
		/// </summary>
		resolve_region,
		/// <summary>
		/// Specifies whether copying query results to a buffer is supported.
		/// If this feature is not present, <see cref="command_list::copy_query_results"/> must not be used.
		/// </summary>
		copy_query_results,
	};

	/// <summary>
	/// The base class for objects provided by the ReShade API.
	/// <para>This lets you store and retrieve custom data with objects, e.g. to be able to communicate persistent information between event callbacks.</para>
	/// </summary>
	struct DECLSPEC_NOVTABLE api_object
	{
		/// <summary>
		/// Gets a custom data pointer from the object that was previously set via <see cref="set_user_data"/>.
		/// This function is not thread-safe!
		/// </summary>
		/// <returns><c>true</c> if a pointer was previously set with this <paramref name="guid"/>, <c>false</c> otherwise.</returns>
		virtual bool get_user_data(const uint8_t guid[16], void **ptr) const = 0;
		/// <summary>
		/// Sets a custom data pointer associated with the specified <paramref name="guid"/> to the object.
		/// You can call this with <paramref name="ptr"/> set to <c>nullptr</c> to remove the pointer associated with the provided <paramref name="guid"/> from this object.
		/// This function is not thread-safe!
		/// </summary>
		virtual void set_user_data(const uint8_t guid[16], void * const ptr) = 0;

		/// <summary>
		/// Gets the underlying native object for this API object.
		/// <para>
		/// For <see cref="device"/> this will be be a pointer to a 'IDirect3DDevice9', 'ID3D10Device', 'ID3D11Device' or 'ID3D12Device' object or a 'HGLRC' or 'VkDevice' handle.<br/>
		/// For <see cref="command_list"/> this will be a pointer to a 'ID3D11DeviceContext' (when recording), 'ID3D11CommandList' (when executing) or 'ID3D12GraphicsCommandList' object or a 'VkCommandBuffer' handle.<br/>
		/// For <see cref="command_queue"/> this will be a pointer to a 'ID3D11DeviceContext' or 'ID3D12CommandQueue' object or a 'VkQueue' handle.<br/>
		/// For <see cref="effect_runtime"/> this will be a pointer to a 'IDirect3DSwapChain9' or 'IDXGISwapChain' object or a 'HDC' or 'VkSwapchainKHR' handle.
		/// </para>
		/// </summary>
		virtual uint64_t get_native_object() const = 0;

		// Helper templates to manage custom data creation and destruction:
		template <typename T> inline T &get_user_data(const uint8_t guid[16]) const
		{
			T *res = nullptr;
			get_user_data(guid, reinterpret_cast<void **>(&res));
			return *res;
		}
		template <typename T> inline T &create_user_data(const uint8_t guid[16])
		{
			T *res = new T();
			set_user_data(guid, res);
			return *res;
		}
		template <typename T> inline void destroy_user_data(const uint8_t guid[16])
		{
			T *res = nullptr;
			get_user_data(guid, reinterpret_cast<void **>(&res));
			delete res;
			set_user_data(guid, nullptr);
		}
	};

	/// <summary>
	/// A logical render device, used for resource creation and global operations.
	/// <para>Functionally equivalent to a 'IDirect3DDevice9', 'ID3D10Device', 'ID3D11Device', 'ID3D12Device', 'HGLRC' or 'VkDevice'.</para>
	/// </summary>
	struct DECLSPEC_NOVTABLE device : public api_object
	{
		/// <summary>
		/// Gets the underlying render API used by this device.
		/// </summary>
		virtual device_api get_api() const = 0;

		/// <summary>
		/// Checks whether the device supports the specfied <paramref name="capability"/>.
		/// </summary>
		virtual bool check_capability(device_caps capability) const = 0;
		/// <summary>
		/// Checks whether the specified <paramref name="format"/> supports the specified <paramref name="usage"/>.
		/// </summary>
		virtual bool check_format_support(format format, resource_usage usage) const = 0;

		/// <summary>
		/// Checks whether the specified <paramref name="resource"/> handle points to a resource that is still alive and valid.
		/// </summary>
		virtual bool is_resource_handle_valid(resource handle) const = 0;
		/// <summary>
		/// Checks whether the specified resource <paramref name="view"/> handle points to a resource view that is still alive and valid.
		/// </summary>
		virtual bool is_resource_view_handle_valid(resource_view handle) const = 0;

		/// <summary>
		/// Creates a new sampler state object based on the specified <paramref name="desc"/>ription.
		/// </summary>
		/// <param name="desc">The description of the sampler to create.</param>
		/// <param name="out">Pointer to a handle that is set to the handle of the created sampler.</param>
		/// <returns><c>true</c> if the sampler was successfully created, <c>false</c> otherwise (in this case <paramref name="out"/> is set to zero).</returns>
		virtual bool create_sampler(const sampler_desc &desc, sampler *out) = 0;
		/// <summary>
		/// Allocates and creates a new resource based on the specified <paramref name="desc"/>ription.
		/// </summary>
		/// <param name="desc">The description of the resource to create.</param>
		/// <param name="initial_data">Optional data to upload to the resource after creation. This should point to an array of <see cref="mapped_subresource"/>, one for each subresource (mipmap levels and array layers). Can be <c>nullptr</c> to indicate no initial data to upload.</param>
		/// <param name="initial_state">Initial state of the resource after creation. This can later be changed via <see cref="command_list::barrier"/>.</param>
		/// <param name="out">Pointer to a handle that is set to the handle of the created resource.</param>
		/// <returns><c>true</c> if the resource was successfully created, <c>false</c> otherwise (in this case <paramref name="out"/> is set to zero).</returns>
		virtual bool create_resource(const resource_desc &desc, const subresource_data *initial_data, resource_usage initial_state, resource *out) = 0;
		/// <summary>
		/// Creates a new resource view for the specified <paramref name="resource"/> based on the specified <paramref name="desc"/>ription.
		/// </summary>
		/// <param name="resource">The resource the view is created for.</param>
		/// <param name="usage_type">The usage type of the resource view to create. Set to <see cref="resource_usage::shader_resource"/> to create a shader resource view, <see cref="resource_usage::depth_stencil"/> for a depth-stencil view, <see cref="resource_usage::render_target"/> for a render target etc.</param>
		/// <param name="desc">The description of the resource to create.</param>
		/// <param name="out">Pointer to a handle that is set to the handle of the created resource view.</param>
		/// <returns><c>true</c> if the resource view was successfully created, <c>false</c> otherwise (in this case <paramref name="out"/> is set to zero).</returns>
		virtual bool create_resource_view(resource resource, resource_usage usage_type, const resource_view_desc &desc, resource_view *out) = 0;

		/// <summary>
		/// Creates a new pipeline state object based on the specified <paramref name="desc"/>ription.
		/// </summary>
		/// <param name="desc">The description of the pipeline state object to create.</param>
		/// <param name="out">Pointer to a handle that is set to the handle of the created pipeline state object.</param>
		/// <returns><c>true</c> if the pipeline state object was successfully created, <c>false</c> otherwise (in this case <paramref name="out"/> is set to zero).</returns>
		virtual bool create_pipeline(const pipeline_desc &desc, pipeline *out) = 0;
		/// <summary>
		/// Creates a new pipeline layout.
		/// </summary>
		/// <param name="out">Pointer to a handle that is set to the handle of the created pipeline layout.</param>
		/// <returns><c>true</c> if the pipeline layout was successfully created, <c>false</c> otherwise (in this case <paramref name="out"/> is set to zero).</returns>
		virtual bool create_pipeline_layout(uint32_t num_set_layouts, const descriptor_set_layout *set_layouts, uint32_t num_constant_ranges, const constant_range *constant_ranges, pipeline_layout *out) = 0;
		/// <summary>
		/// Creates a new descriptor set layout.
		/// </summary>
		/// <param name="num_ranges">The number of descriptor ranges.</param>
		/// <param name="ranges">A pointer to an array of descriptor ranges contained in the descriptor set this layout describes.</param>
		/// <param name="push_descriptors"><c>true</c> if this layout is later used with <see cref="command_list::push_descriptors"/>, <c>false</c> if not.</param>
		/// <param name="out">Pointer to a handle that is set to the handle of the created descriptor set layout.</param>
		/// <returns><c>true</c> if the descriptor set layout was successfully created, <c>false</c> otherwise (in this case <paramref name="out"/> is set to zero).</returns>
		virtual bool create_descriptor_set_layout(uint32_t num_ranges, const descriptor_range *ranges, bool push_descriptors, descriptor_set_layout *out) = 0;
		/// <summary>
		/// Creates a new query pool.
		/// </summary>
		/// <param name="type">The type of queries that will be used with this pool.</param>
		/// <param name="count">The number of queries to allocate in the pool.</param>
		/// <param name="out">Pointer to a handle that is set to the handle of the created query pool.</param>
		/// <returns><c>true</c> if the query pool was successfully created, <c>false</c> otherwise (in this case <paramref name="out"/> is set to zero).</returns>
		virtual bool create_query_pool(query_type type, uint32_t count, query_pool *out) = 0;
		/// <summary>
		/// Allocates one or more descriptor sets.
		/// </summary>
		/// <param name="layout">The layout of the descriptor sets.</param>
		/// <param name="count">The number of descriptor sets to allocate.</param>
		/// <param name="out">Pointer to an array of handles with at least <paramref name="count"/> elements that is filles with the handles of the created descriptor sets.</param>
		/// <returns><c>true</c> if the descriptor sets were successfully created, <c>false</c> otherwise (in this case <paramref name="out"/> is filles with zeroes).</returns>
		virtual bool create_descriptor_sets(descriptor_set_layout layout, uint32_t count, descriptor_set *out) = 0;

		/// <summary>
		/// Instantly destroys a sampler that was previously created via <see cref="create_sampler"/>.
		/// </summary>
		virtual void destroy_sampler(sampler handle) = 0;
		/// <summary>
		/// Instantly destroys a resource that was previously created via <see cref="create_resource"/> and frees its memory.
		/// <para>Make sure the resource is no longer in use on the GPU (via any command list that may reference it and is still being executed) before doing this and never try to destroy resources created by the application!</para>
		/// </summary>
		virtual void destroy_resource(resource handle) = 0;
		/// <summary>
		/// Instantly destroys a resource view that was previously created via <see cref="create_resource_view"/>.
		/// </summary>
		virtual void destroy_resource_view(resource_view handle) = 0;

		/// <summary>
		/// Instantly destroys a pipeline state object that was previously created via <see cref="create_pipeline"/>.
		/// </summary>
		/// <param name="type">The type of the pipeline state object.</param>
		virtual void destroy_pipeline(pipeline_type type, pipeline handle) = 0;
		/// <summary>
		/// Instantly destroys a pipeline layout that was previously created via <see cref="create_pipeline_layout"/>.
		/// </summary>
		virtual void destroy_pipeline_layout(pipeline_layout handle) = 0;
		/// <summary>
		/// Instantly destroys a descriptor set layout that was previously created via <see cref="create_descriptor_set_layout"/>.
		/// </summary>
		virtual void destroy_descriptor_set_layout(descriptor_set_layout handle) = 0;
		/// <summary>
		/// Instantly destroys a query pool that was previously created via <see cref="create_query_pool"/>.
		/// </summary>
		virtual void destroy_query_pool(query_pool handle) = 0;
		/// <summary>
		/// Frees one or more descriptor sets that were previously created via <see cref="create_descriptor_sets"/>.
		/// </summary>
		virtual void destroy_descriptor_sets(descriptor_set_layout layout, uint32_t count, const descriptor_set *sets) = 0;

		/// <summary>
		/// Gets the handle to the underlying resource the specified resource <paramref name="view"/> was created for.
		/// </summary>
		virtual void get_resource_from_view(resource_view view, resource *resource) const = 0;
		/// <summary>
		/// Gets the description of the specified <paramref name="resource"/>.
		/// </summary>
		/// <param name="resource">The resource to get the description from.</param>
		virtual resource_desc get_resource_desc(resource resource) const = 0;

		/// <summary>
		/// Maps the memory of a resource into application address space.
		/// </summary>
		/// <param name="resource">The resource to map.</param>
		/// <param name="subresource">The index of the subresource.</param>
		/// <param name="access">A hint on how the returned data pointer will be accessed.</param>
		/// <param name="data">Pointer to a pointer that is set to a pointer to the memory of the resource.</param>
		/// <returns><c>true</c> if the memory of the resource was successfully mapped, <c>false</c> otherwise (in this case <paramref name="data"/> is set to <c>nullptr</c>).</returns>
		virtual bool map_resource(resource resource, uint32_t subresource, map_access access, void **data) = 0;
		/// <summary>
		/// Unmaps a previously mapped resource.
		/// </summary>
		/// <param name="resource">The resource to unmap.</param>
		/// <param name="subresource">The index of the subresource.</param>
		virtual void unmap_resource(resource resource, uint32_t subresource) = 0;

		/// <summary>
		/// Uploads data to a buffer resource.
		/// </summary>
		/// <param name="data">Pointer to the data to upload.</param>
		/// <param name="destination">The buffer resource to upload to.</param>
		/// <param name="dst_offset">An offset (in bytes) into the buffer <paramref name="resource"/> to start uploading to.</param>
		/// <param name="size">The number of bytes to upload.</param>
		virtual void upload_buffer_region(const void *data, resource destination, uint64_t dst_offset, uint64_t size) = 0;
		/// <summary>
		/// Uploads data to a texture resource.
		/// </summary>
		/// <param name="data">Pointer to the data to upload.</param>
		/// <param name="destination">The texture resource to upload to.</param>
		/// <param name="dst_subresource">The subresource of the <paramref name="resource"/> to upload to.</param>
		/// <param name="dst_box">A 3D box (or <c>nullptr</c> to reference the entire subresource) that defines the region in the <paramref name="resource"/> to upload to, in the format { left, top, front, right, bottom, back }.</param>
		virtual void upload_texture_region(const subresource_data &data, resource destination, uint32_t dst_subresource, const int32_t dst_box[6] = nullptr) = 0;
		/// <summary>
		/// Updates the contents of descriptor sets with the specified descriptors.
		/// </summary>
		/// <param name="count">The number of updates to process.</param>
		/// <param name="updates">A pointer to an array of updates to process.</param>
		virtual void update_descriptor_sets(uint32_t count, const descriptor_update *updates) = 0;

		/// <summary>
		/// Gets the results of queries in a query pool.
		/// </summary>
		/// <param name="pool">The query pool that manages the results of the queries.</param>
		/// <param name="first">The index of the first query in the pool to copy the result from.</param>
		/// <param name="count">The number of query results to copy.</param>
		/// <param name="results">Pointer to an array that is filled with the results.</param>
		/// <param name="stride">The size (in bytes) of each result element.</param>
		/// <returns><c>true</c> if the query results were successfully downloaded from the GPU, <c>false</c> otherwise.</returns>
		virtual bool get_query_results(query_pool pool, uint32_t first, uint32_t count, void *results, uint32_t stride) = 0;

		/// <summary>
		/// Waits for all issued GPU operations to finish before returning.
		/// This can be used to ensure that e.g. resources are no longer in use on the GPU before destroying them.
		/// </summary>
		virtual void wait_idle() const = 0;

		/// <summary>
		/// Associates a name with a resource, which is used by debugging tools.
		/// </summary>
		/// <param name="resource">The resource to set the debug name for.</param>
		/// <param name="name">A null-terminated debug name string.</param>
		virtual void set_debug_name(resource resource, const char *name) = 0;
	};

	/// <summary>
	/// The base class for objects that are children to a logical render <see cref="device"/>.
	/// </summary>
	struct DECLSPEC_NOVTABLE device_object : public api_object
	{
		/// <summary>
		/// Gets the parent device for this object.
		/// </summary>
		virtual device *get_device() = 0;
	};

	/// <summary>
	/// A command list, used to enqueue render commands on the CPU, before later executing them in a command queue.
	/// <para>Functionally equivalent to a 'ID3D11CommandList', 'ID3D12CommandList' or 'VkCommandBuffer'.</para>
	/// </summary>
	struct DECLSPEC_NOVTABLE command_list : public device_object
	{
		/// <summary>
		/// Adds a barrier for the specified <paramref name="resource"/> to the command stream.
		/// When both <paramref name="old_state"/> and <paramref name="new_state"/> are <see cref="resource_usage::unordered_access"/> a UAV barrier is added, otherwise a state transition is performed.
		/// </summary>
		/// <param name="resource">The resource to transition.</param>
		/// <param name="old_state">The usage flags describing how the resource was used before this barrier.</param>
		/// <param name="new_state">The usage flags describing how the resource will be used after this barrier.</param>
		inline  void barrier(resource resource, resource_usage old_state, resource_usage new_state) { barrier(1, &resource, &old_state, &new_state); }
		/// <summary>
		/// Adds a barrier for the specified <paramref name="resources"/> to the command stream.
		/// </summary>
		/// <param name="count">The number of resources to transition.</param>
		/// <param name="resources">A pointer to an array of resources to transition.</param>
		/// <param name="old_states">A pointer to an array of usage flags describing how the resources were used before this barrier.</param>
		/// <param name="new_states">A pointer to an array of usage flags describing how the resources will be used after this barrier.</param>
		virtual void barrier(uint32_t count, const resource *resources, const resource_usage *old_states, const resource_usage *new_states) = 0;

		/// <summary>
		/// Binds a pipeline state object.
		/// </summary>
		/// <param name="type">The pipeline state object type to bind.</param>
		/// <param name="pipeline">The pipeline state object to bind.</param>
		virtual void bind_pipeline(pipeline_type type, pipeline pipeline) = 0;
		/// <summary>
		/// Directly sets individual dynamic pipeline states to the specified values.
		/// </summary>
		/// <param name="count">The number of pipeline states to set.</param>
		/// <param name="states">A pointer to an array of pipeline states to set.</param>
		/// <param name="values">A pointer to an array of pipeline state values, with one for each state in <paramref name="states"/>.</param>
		virtual void bind_pipeline_states(uint32_t count, const pipeline_state *states, const uint32_t *values) = 0;
		/// <summary>
		/// Binds an array of viewports to the rasterizer stage.
		/// </summary>
		/// <param name="first">The index of the first viewport to bind. In D3D9, D3D10, D3D11 and D3D12 this has to be 0.</param>
		/// <param name="count">The number of viewports to bind. In D3D9 this has to be 1.</param>
		/// <param name="viewports">A pointer to an array of viewports in the format { x 0, y 0, width 0, height 0, min depth 0, max depth 0, x 1, y 1, width 1, height 1, ... }.</param>
		virtual void bind_viewports(uint32_t first, uint32_t count, const float *viewports) = 0;
		/// <summary>
		/// Binds an array of scissor rectangles to the rasterizer stage.
		/// </summary>
		/// <param name="first">The index of the first scissor rectangle to bind. In D3D9, D3D10, D3D11 and D3D12 this has to be 0.</param>
		/// <param name="count">The number of scissor rectangles to bind. In D3D9 this has to be 1.</param>
		/// <param name="rects">A pointer to an array of scissor rectangles in the format { left 0, top 0, right 0, bottom 0, left 1, top 1, right 1, ... }.</param>
		virtual void bind_scissor_rects(uint32_t first, uint32_t count, const int32_t *rects) = 0;

		/// <summary>
		/// Directly updates constant values in the specified shader pipeline stage.
		/// <para>In D3D9 this updates the values of uniform registers, in D3D10/11 and OpenGL the constant buffer specified in the pipeline layout, in D3D12 it sets root constants and in Vulkan push constants.</para>
		/// </summary>
		/// <param name="stage">The shader stages that will use the updated constants.</param>
		/// <param name="layout">The pipeline layout that describes where the constants are located.</param>
		/// <param name="layout_index">The index of the constant range in the pipeline <paramref name="layout"/>.</param>
		/// <param name="first">The start offset (in 32-bit values) to the first constant in the constant range to begin updating.</param>
		/// <param name="count">The number of 32-bit values to update.</param>
		/// <param name="values">A pointer to an array of 32-bit values to set the constants to. These can be floating-point, integer or boolean depending on what the shader is expecting.</param>
		virtual void push_constants(shader_stage stage, pipeline_layout layout, uint32_t layout_index, uint32_t first, uint32_t count, const void *values) = 0;
		/// <summary>
		/// Directly updates a descriptor set for the specfified shader pipeline stage with an array of descriptors.
		/// </summary>
		/// <param name="stage">The shader stages that will use the updated descriptors.</param>
		/// <param name="layout">The pipeline layout that describes the descriptors.</param>
		/// <param name="layout_index">The index of the descriptor set in the pipeline <paramref name="layout"/>.</param>
		/// <param name="type">The type of descriptors to bind.</param>
		/// <param name="first">The first binding in the descriptor set to update.</param>
		/// <param name="count">The number of descriptors to update.</param>
		/// <param name="descriptors">A pointer to an array of descriptors to update in the set. Depending on the descriptor <paramref name="type"/> this should pointer to an array of <see cref="resource"/>, <see cref="resource_view"/>, <see cref="sampler"/> or <see cref="sampler_with_resource_view"/>.</param>
		virtual void push_descriptors(shader_stage stage, pipeline_layout layout, uint32_t layout_index, descriptor_type type, uint32_t first, uint32_t count, const void *descriptors) = 0;
		/// <summary>
		/// Binds an array of descriptor sets.
		/// <para>This is not supported (and will do nothing) in D3D9, D3D10, D3D11 and OpenGL.</para>
		/// </summary>
		/// <param name="type">The pipeline type that will use the descriptors.</param>
		/// <param name="layout">The pipeline layout that describes the descriptors.</param>
		/// <param name="first">The index of the first descriptor set in the pipeline <paramref name="layout"/> to bind.</param>
		/// <param name="count">The number of descriptor sets to bind.</param>
		/// <param name="sets">A pointer to an array of descriptor sets to bind.</param>
		virtual void bind_descriptor_sets(pipeline_type type, pipeline_layout layout, uint32_t first, uint32_t count, const descriptor_set *sets) = 0;

		/// <summary>
		/// Binds an index buffer to the input-assembler stage.
		/// </summary>
		/// <param name="buffer">The index buffer resource. This resource must have been created with the <see cref="resource_usage::index_buffer"/> usage.</param>
		/// <param name="offset">Offset (in bytes) from the start of the index buffer to the first index to use. In D3D9 this has to be 0.</param>
		/// <param name="index_size">The size (in bytes) of each index. Can typically be 2 (16-bit indices) or 4 (32-bit indices).</param>
		virtual void bind_index_buffer(resource buffer, uint64_t offset, uint32_t index_size) = 0;
		/// <summary>
		/// Binds a single vertex buffer to the input-assembler stage.
		/// </summary>
		/// <param name="index">The input slot for binding.</param>
		/// <param name="buffer">The vertex buffer resource. This resources must have been created with the <see cref="resource_usage::vertex_buffer"/> usage.</param>
		/// <param name="offset">Offset (in bytes) from the start of the vertex buffer to the first vertex element to use.</param>
		/// <param name="stride">The size (in bytes) of the vertex element that will be used from the vertex buffer (is added to an element offset to advance to the next).</param>
		inline  void bind_vertex_buffer(uint32_t index, resource buffer, uint64_t offset, uint32_t stride) { bind_vertex_buffers(index, 1, &buffer, &offset, &stride); }
		/// <summary>
		/// Binds an array of vertex buffers to the input-assembler stage.
		/// </summary>
		/// <param name="first">The first input slot for binding.</param>
		/// <param name="count">The number of vertex buffers to bind.</param>
		/// <param name="buffers">A pointer to an array of vertex buffer resources. These resources must have been created with the <see cref="resource_usage::vertex_buffer"/> usage.</param>
		/// <param name="offsets">A pointer to an array of offset values, with one for each buffer in <paramref name="buffers"/>. Each offset is the number of bytes from the start of the vertex buffer to the first vertex element to use.</param>
		/// <param name="strides">A pointer to an array of stride values, with one for each buffer in <paramref name="strides"/>. Each stride is the size (in bytes) of the vertex element that will be used from that vertex buffer (is added to an element offset to advance to the next).</param>
		virtual void bind_vertex_buffers(uint32_t first, uint32_t count, const resource *buffers, const uint64_t *offsets, const uint32_t *strides) = 0;

		/// <summary>
		/// Draws non-indexed primitives.
		/// </summary>
		/// <param name="vertices">The number of vertices to draw.</param>
		/// <param name="instances">The number of instances to draw. In D3D9 this has to be 1.</param>
		/// <param name="first_vertex">Index of the first vertex.</param>
		/// <param name="first_instance">A value added to each index before reading per-instance data from a vertex buffer. In D3D9 this has to be 0.</param>
		virtual void draw(uint32_t vertices, uint32_t instances, uint32_t first_vertex, uint32_t first_instance) = 0;
		/// <summary>
		/// Draws indexed primitives.
		/// </summary>
		/// <param name="indices">The number of indices read from the index buffer for each instance.</param>
		/// <param name="instances">The number of instances to draw. In D3D9 this has to be 1.</param>
		/// <param name="first_index">The location of the first index read from the index buffer.</param>
		/// <param name="vertex_offset">A value added to each index before reading per-vertex data from a vertex buffer.</param>
		/// <param name="first_instance">A value added to each index before reading per-instance data from a vertex buffer. In D3D9 this has to be 0.</param>
		virtual void draw_indexed(uint32_t indices, uint32_t instances, uint32_t first_index, int32_t vertex_offset, uint32_t first_instance) = 0;
		/// <summary>
		/// Performs a compute shader dispatch.
		/// This is not supported (and will do nothing) in D3D9 and D3D10.
		/// </summary>
		/// <param name="num_groups_x">The number of thread groups dispatched in the x direction.</param>
		/// <param name="num_groups_y">The number of thread groups dispatched in the y direction.</param>
		/// <param name="num_groups_z">The number of thread groups dispatched in the z direction.</param>
		virtual void dispatch(uint32_t num_groups_x, uint32_t num_groups_y, uint32_t num_groups_z) = 0;
		/// <summary>
		/// Executes indirect draw or dispatch commands.
		/// This is not supported (and will do nothing) in D3D9 and D3D10.
		/// </summary>
		/// <param name="type">Specifies whether this is an indirect draw, indexed draw or dispatch command: <c>1</c> for draw commands, <c>2</c> for indexed draw commands and <c>3</c> for dispatch commands</param>
		/// <param name="buffer">The buffer that contains command arguments.</param>
		/// <param name="offset">Offset (in bytes) from the start of the argument buffer to the first argument to use.</param>
		/// <param name="draw_count">The number of commands to execute.</param>
		/// <param name="stride">The stride between commands in the argument buffer.</param>
		virtual void draw_or_dispatch_indirect(uint32_t type, resource buffer, uint64_t offset, uint32_t draw_count, uint32_t stride) = 0;

		/// <summary>
		/// Marks the beginning of a render pass by binding one or more render targets and the depth-stencil buffer to the output-merger stage.
		/// </summary>
		/// <param name="count">The number of render targets to bind.</param>
		/// <param name="rtvs">A pointer to an array of resource views that represent the render targets to bind. The resources these point to must have been created with the <see cref="resource_usage::render_target"/> usage.</param>
		/// <param name="dsv">The resource view that represents the depth-stencil buffer to bind (or zero to bind none). The resource this points to must have been created with the <see cref="resource_usage::depth_stencil"/> usage.</param>
		virtual void begin_render_pass(uint32_t count, const resource_view *rtvs, resource_view dsv = { 0 }) = 0;
		/// <summary>
		/// Marks the ending of a render pass.
		/// This must be preceeded by a call to <see cref="begin_render_pass"/>). Render passes cannot be nested.
		/// </summary>
		virtual void finish_render_pass() = 0;

		/// <summary>
		/// Copies the entire contents of the <paramref name="source"/> resource to the <paramref name="destination"/> resource. Dimensions of the two resources need to match.
		/// <para>The <paramref name="source"/> resource has to be in the <see cref="resource_usage::copy_source"/> state.</para>
		/// <para>The <paramref name="destination"/> resource has to be in the <see cref="resource_usage::copy_dest"/> state.</para>
		/// </summary>
		/// <param name="source">The resource to copy from.</param>
		/// <param name="destination">The resource to copy to.</param>
		virtual void copy_resource(resource source, resource destination) = 0;
		/// <summary>
		/// Copies a linear memory region from the <paramref name="source"/> buffer to the <paramref name="destination"/> buffer.
		/// This is not supported (and will do nothing) in D3D9.
		/// <para>The <paramref name="source"/> resource has to be in the <see cref="resource_usage::copy_source"/> state.</para>
		/// <para>The <paramref name="destination"/> resource has to be in the <see cref="resource_usage::copy_dest"/> state.</para>
		/// </summary>
		/// <param name="source">The buffer to copy from.</param>
		/// <param name="src_offset">An offset (in bytes) into the <paramref name="source"/> buffer to start copying at.</param>
		/// <param name="destination">The buffer to copy to.</param>
		/// <param name="dst_offset">An offset (in bytes) into the <paramref name="destination"/> buffer to start copying to.</param>
		/// <param name="size">The number of bytes to copy.</param>
		virtual void copy_buffer_region(resource source, uint64_t src_offset, resource destination, uint64_t dst_offset, uint64_t size) = 0;
		/// <summary>
		/// Copies a texture region from the <paramref name="source"/> buffer to the <paramref name="destination"/> texture.
		/// <para>The <paramref name="source"/> resource has to be in the <see cref="resource_usage::copy_source"/> state.</para>
		/// <para>The <paramref name="destination"/> resource has to be in the <see cref="resource_usage::copy_dest"/> state.</para>
		/// </summary>
		/// <param name="source">The buffer to copy from.</param>
		/// <param name="src_offset">An offset (in bytes) into the <paramref name="source"/> buffer to start copying at.</param>
		/// <param name="row_length">The number of pixels from one row to the next (in the buffer), or zero if data is tightly packed.</param>
		/// <param name="slice_height">The number of rows from one slice to the next (in the buffer) or zero if data is tightly packed.</param>
		/// <param name="destination">The texture to copy to.</param>
		/// <param name="dst_subresource">The subresource of the <paramref name="destination"/> texture to copy to.</param>
		/// <param name="dst_box">A 3D box (or <c>nullptr</c> to reference the entire subresource) that defines the region in the <paramref name="destination"/> texture to copy to, in the format { left, top, front, right, bottom, back }.</param>
		virtual void copy_buffer_to_texture(resource source, uint64_t src_offset, uint32_t row_length, uint32_t slice_height, resource destination, uint32_t dst_subresource, const int32_t dst_box[6] = nullptr) = 0;
		/// <summary>
		/// Copies or blits a texture region from the <paramref name="source"/> texture to the <paramref name="destination"/> texture.
		/// <para>The <paramref name="source"/> resource has to be in the <see cref="resource_usage::copy_source"/> state.</para>
		/// <para>The <paramref name="destination"/> resource has to be in the <see cref="resource_usage::copy_dest"/> state.</para>
		/// </summary>
		/// <param name="source">The texture to copy from.</param>
		/// <param name="src_subresource">The subresource of the <paramref name="source"/> texture to copy from.</param>
		/// <param name="src_box">A 3D box (or <c>nullptr</c> to reference the entire subresource) that defines the region in the <paramref name="source"/> resource to blit from, in the format { left, top, front, right, bottom, back }.</param>
		/// <param name="destination">The texture to copy to.</param>
		/// <param name="dst_subresource">The subresource of the <paramref name="destination"/> texture to copy to.</param>
		/// <param name="dst_box">A 3D box (or <c>nullptr</c> to reference the entire subresource) that defines the region in the <paramref name="destination"/> resource to blit to, in the format { left, top, front, right, bottom, back }.</param>
		/// <param name="filter">The filter to apply when copy requires scaling.</param>
		virtual void copy_texture_region(resource source, uint32_t src_subresource, const int32_t src_box[6], resource destination, uint32_t dst_subresource, const int32_t dst_box[6], texture_filter filter = texture_filter::min_mag_mip_point) = 0;
		/// <summary>
		/// Copies a texture region from the <paramref name="source"/> texture to the <paramref name="destination"/> buffer.
		/// <para>The <paramref name="source"/> resource has to be in the <see cref="resource_usage::copy_source"/> state.</para>
		/// <para>The <paramref name="destination"/> resource has to be in the <see cref="resource_usage::copy_dest"/> state.</para>
		/// </summary>
		/// <param name="source">The texture to copy from.</param>
		/// <param name="src_subresource">The subresource of the <paramref name="source"/> texture to copy from.</param>
		/// <param name="src_box">A 3D box (or <c>nullptr</c> to reference the entire subresource) that defines the region in the <paramref name="source"/> texture to copy from, in the format { left, top, front, right, bottom, back }.</param>
		/// <param name="destination">The buffer to copy to.</param>
		/// <param name="dst_offset">An offset (in bytes) into the <paramref name="destination"/> buffer to start copying to.</param>
		/// <param name="row_length">The number of pixels from one row to the next (in the buffer), or zero if data is tightly packed.</param>
		/// <param name="slice_height">The number of rows from one slice to the next (in the buffer), or zero if data is tightly packed.</param>
		virtual void copy_texture_to_buffer(resource source, uint32_t src_subresource, const int32_t src_box[6], resource destination, uint64_t dst_offset, uint32_t row_length = 0, uint32_t slice_height = 0) = 0;
		/// <summary>
		/// Copies a region from the multisampled <paramref name="source"/> texture to the non-multisampled <paramref name="destination"/> texture.
		/// <para>The <paramref name="source"/> resource has to be in the <see cref="resource_usage::resolve_source"/> state.</para>
		/// <para>The <paramref name="destination"/> resource has to be in the <see cref="resource_usage::resolve_dest"/> state.</para>
		/// </summary>
		/// <param name="source">The texture to resolve from.</param>
		/// <param name="src_subresource">The subresource of the <paramref name="source"/> texture to resolve from.</param>
		/// <param name="src_box">A 2D rectangle (or <c>nullptr</c> to reference the entire subresource) that defines the region in the <paramref name="source"/> texture to resolve, in the format { left, top, front, right, bottom, back }. In D3D10 and D3D11 this has to be <c>nullptr</c>.</param>
		/// <param name="destination">The texture to resolve to.</param>
		/// <param name="dst_subresource">The subresource of the <paramref name="destination"/> texture to resolve to.</param>
		/// <param name="dst_offset">An offset (in texels) that defines the region in the <paramref name="destination"/> texture to resolve to, in the format { left, top, front }. In D3D10 and D3D11 this has to be <c>nullptr</c>.</param>
		/// <param name="format">The format of the resource data.</param>
		virtual void resolve_texture_region(resource source, uint32_t src_subresource, const int32_t src_box[6], resource destination, uint32_t dst_subresource, const int32_t dst_offset[3], format format) = 0;

		/// <summary>
		/// Generates the lower mipmap levels for the specified shader resource view.
		/// Uses the largest mipmap level of the view to recursively generate the lower levels of the mip and stops with the smallest level that is specified by the view.
		/// <para>The resource the <paramref name="srv"/> view points to has to be in the <see cref="resource_usage::shader_resource"/> state and has to have been created with the <see cref="resource_flags::generate_mipmaps"/> flag.</para>
		/// </summary>
		/// <param name="srv">The shader resource view to update.</param>
		virtual void generate_mipmaps(resource_view srv) = 0;

		/// <summary>
		/// Clears the resource referenced by the depth-stencil view.
		/// <para>The resource the <paramref name="dsv"/> view points to has to be in the <see cref="resource_usage::depth_stencil_write"/> state.</para>
		/// </summary>
		/// <param name="dsv">The view handle of the depth-stencil.</param>
		/// <param name="clear_flags">A combination of flags to identify which types of data to clear: <c>0x1</c> for depth, <c>0x2</c> for stencil</param>
		/// <param name="depth">The value to clear the depth buffer with.</param>
		/// <param name="stencil">The value to clear the stencil buffer with.</param>
		virtual void clear_depth_stencil_view(resource_view dsv, uint32_t clear_flags, float depth, uint8_t stencil) = 0;
		/// <summary>
		/// Clears the resources referenced by the render target view.
		/// <para>The resource the <paramref name="rtv"/> view point to has to be in the <see cref="resource_usage::render_target"/> state.</para>
		/// </summary>
		/// <param name="rtv">The view handle of the render target.</param>
		/// <param name="color">The value to clear the resource with.</param>
		inline  void clear_render_target_view(resource_view rtv, const float color[4]) { clear_render_target_views(1, &rtv, color); }
		/// <summary>
		/// Clears the resources referenced by the render target views.
		/// <para>The resources the <paramref name="rtvs"/> views point to have to be in the <see cref="resource_usage::render_target"/> state.</para>
		/// </summary>
		/// <param name="count">The number of render target views to clear.</param>
		/// <param name="rtvs">A pointer to an array of render target view handles to clear.</param>
		/// <param name="color">The value to clear the resources with.</param>
		virtual void clear_render_target_views(uint32_t count, const resource_view *rtvs, const float color[4]) = 0;
		/// <summary>
		/// Clears the resource referenced by the unordered access view.
		/// <para>The resources the <paramref name="uav"/> view points to has to be in the <see cref="resource_usage::unordered_access"/> state.</para>
		/// </summary>
		/// <param name="uav">The view handle of the resource.</param>
		/// <param name="values">The value to clear the resources with.</param>
		virtual void clear_unordered_access_view_uint(resource_view uav, const uint32_t values[4]) = 0;
		/// <summary>
		/// Clears the resource referenced by the unordered access view.
		/// <para>The resources the <paramref name="uav"/> view points to has to be in the <see cref="resource_usage::unordered_access"/> state.</para>
		/// </summary>
		/// <param name="uav">The view handle of the resource.</param>
		/// <param name="values">The value to clear the resources with.</param>
		virtual void clear_unordered_access_view_float(resource_view uav, const float values[4]) = 0;

		/// <summary>
		/// Begins a query.
		/// </summary>
		/// <param name="pool">The query pool that will manage the results of the query.</param>
		/// <param name="type">The type of the query to begin.</param>
		/// <param name="index">The index of the query in the pool.</param>
		virtual void begin_query(query_pool pool, query_type type, uint32_t index) = 0;
		/// <summary>
		/// Ends a query.
		/// </summary>
		/// <param name="pool">The query pool that will manage the results of the query.</param>
		/// <param name="type">The type of the query end.</param>
		/// <param name="index">The index of the query in the pool.</param>
		virtual void finish_query(query_pool pool, query_type type, uint32_t index) = 0;
		/// <summary>
		/// Copy the results of queries in a query pool to a buffer resource.
		/// <para>The <paramref name="destination"/> resource has to be in the <see cref="resource_usage::copy_dest"/> state.</para>
		/// </summary>
		/// <param name="pool">The query pool that manages the results of the queries.</param>
		/// <param name="type">The type of the queries to copy.</param>
		/// <param name="first">The index of the first query in the pool to copy the result from.</param>
		/// <param name="count">The number of query results to copy.</param>
		/// <param name="destination">The buffer to copy to.</param>
		/// <param name="dst_offset">An offset (in bytes) into the <paramref name="destination"/> buffer to start copying to.</param>
		/// <param name="stride">The size (in bytes) of each result element.</param>
		virtual void copy_query_results(query_pool pool, query_type type, uint32_t first, uint32_t count, resource destination, uint64_t dst_offset, uint32_t stride) = 0;

		/// <summary>
		/// Inserts a debug marker into the command list.
		/// </summary>
		/// <param name="label">A null-terminated string containing the label of the debug marker.</param>
		/// <param name="color">An optional RGBA color value associated with the debug marker.</param>
		virtual void add_debug_marker(const char *label, const float color[4] = nullptr) = 0;
		/// <summary>
		/// Opens a debug marker region in the command list.
		/// </summary>
		/// <param name="label">A null-terminated string containing the label of the debug marker.</param>
		/// <param name="color">An optional RGBA color value associated with the debug marker.</param>
		virtual void begin_debug_marker(const char *label, const float color[4] = nullptr) = 0;
		/// <summary>
		/// Closes the current debug marker region (the last one opened with <see cref="begin_debug_marker"/>).
		/// </summary>
		virtual void finish_debug_marker() = 0;
	};

	/// <summary>
	/// A command queue, used to execute command lists on the GPU.
	/// <para>Functionally equivalent to the immediate 'ID3D11DeviceContext' or a 'ID3D12CommandQueue' or 'VkQueue'.</para>
	/// </summary>
	struct DECLSPEC_NOVTABLE command_queue : public device_object
	{
		/// <summary>
		/// Gets a special command list, on which all issued commands are executed as soon as possible (or right before the application executes its next command list on this queue).
		/// </summary>
		virtual command_list *get_immediate_command_list() = 0;

		/// <summary>
		/// Flushes and executes the special immediate command list returned by <see cref="get_immediate_command_list"/> immediately.
		/// This can be used to force commands to execute right away instead of waiting for the runtime to flush it automatically at some point.
		/// </summary>
		virtual void flush_immediate_command_list() const  = 0;

		/// <summary>
		/// Waits for all issued GPU operations on this queue to finish before returning.
		/// This can be used to ensure that e.g. resources are no longer in use on the GPU before destroying them.
		/// </summary>
		virtual void wait_idle() const = 0;

		/// <summary>
		/// Inserts a debug marker into the command queue.
		/// </summary>
		/// <param name="label">A null-terminated string containing the label of the debug marker.</param>
		/// <param name="color">An optional RGBA color value associated with the debug marker.</param>
		virtual void add_debug_marker(const char *label, const float color[4] = nullptr) = 0;
		/// <summary>
		/// Opens a debug marker region in the command queue.
		/// </summary>
		/// <param name="label">A null-terminated string containing the label of the debug marker.</param>
		/// <param name="color">An optional RGBA color value associated with the debug marker.</param>
		virtual void begin_debug_marker(const char *label, const float color[4] = nullptr) = 0;
		/// <summary>
		/// Closes the current debug marker region (the last one opened with <see cref="begin_debug_marker"/>).
		/// </summary>
		virtual void finish_debug_marker() = 0;
	};

	/// <summary>
	/// A ReShade effect runtime, used to control effects.
	/// <para>A separate runtime is instantiated for every swap chain ('IDirect3DSwapChain9', 'IDXGISwapChain', 'HDC' or 'VkSwapchainKHR').</para>
	/// </summary>
	struct DECLSPEC_NOVTABLE effect_runtime : public device_object
	{
		/// <summary>
		/// Gets the main graphics command queue associated with this effect runtime.
		/// This may potentially be different from the presentation queue and should be used to execute graphics commands on.
		/// </summary>
		virtual command_queue *get_command_queue() = 0;

		/// <summary>
		/// Gets the current buffer dimensions of the swap chain.
		/// </summary>
		virtual void get_frame_width_and_height(uint32_t *width, uint32_t *height) const = 0;

		/// <summary>
		/// Updates all textures that use the specified <paramref name="semantic"/> in all active effects to new resource view.
		/// </summary>
		virtual void update_texture_bindings(const char *semantic, resource_view shader_resource_view) = 0;

		/// <summary>
		/// Updates the values of all uniform variables with a "source" annotation set to <paramref name="source"/> to the specified <paramref name="values"/>.
		/// </summary>
		virtual void update_uniform_variables(const char *source, const bool *values, size_t count, size_t array_index = 0) = 0;
		virtual void update_uniform_variables(const char *source, const float *values, size_t count, size_t array_index = 0) = 0;
		virtual void update_uniform_variables(const char *source, const int32_t *values, size_t count, size_t array_index = 0) = 0;
		virtual void update_uniform_variables(const char *source, const uint32_t *values, size_t count, size_t array_index = 0) = 0;
	};
} }
