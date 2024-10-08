#include "pch.h"
#include "ViewportManager.h"

using namespace DirectX;
using namespace MattMath;
using namespace viewport_consts;

Viewport ViewportManager::get_fullscreen_viewport() const
{
    Vector2F res = this->_resolution_manager->get_resolution_vec();
    return Viewport(0.0f, 0.0f, res.x, res.y);
}

D3D11_VIEWPORT ViewportManager::get_fullscreen_d3d11_viewport() const
{
    Viewport vp = this->get_fullscreen_viewport();
    return vp.get_d3d_viewport();
}

//void ViewportManager::apply_fullscreen_viewport()
//{
//    D3D11_VIEWPORT vp = this->get_fullscreen_d3d11_viewport();
//    auto context = this->_device_resources->GetD3DDeviceContext();
//
//    D3D11_VIEWPORT vp2 = this->get_fullscreen_d3d11_viewport();
//
//    //D3D11_VIEWPORT* vps = new D3D11_VIEWPORT[2];
//    //vps[0] = vp;
//    //vps[1] = vp2;
//    this->_test_vps[0] = vp;
//    this->_test_vps[1] = vp2;
//
//    context->RSSetViewports(2, this->_test_vps);
//
//    //context->RSSetViewports(1, &vp);
//    this->_sprite_batch->SetViewport(vp);
//}

RectangleF ViewportManager::get_camera_adjusted_player_viewport_rect(
    int player_num, const Camera& camera) const
{
	Viewport vp = this->get_player_viewport(player_num);
    const float scale = camera.scale;
    const Vector2F& translation = camera.translation;

    RectangleF result = RectangleF(
		translation.x,
		translation.y,
		vp.width * scale,
		vp.height * scale);

	return result;
}

void ViewportManager::apply_player_viewport(int player_num)
{
	D3D11_VIEWPORT vp = this->calculate_d3d11_viewport(
        this->_layout, player_num, this->_resolution_manager->get_resolution_vec());
	auto context = this->_device_resources->GetD3DDeviceContext();
	context->RSSetViewports(1, &vp);
	this->_sprite_batch->SetViewport(vp);
}

D3D11_VIEWPORT ViewportManager::calculate_d3d11_viewport(screen_layout layout,
    int player_num, const Vector2F& screen_size) const
{
	Viewport vp = this->calculate_viewport(layout, player_num, screen_size);
	//return static_cast<D3D11_VIEWPORT>(vp);
    return vp.get_d3d_viewport();
}

void ViewportManager::set_layout(screen_layout layout)
{
    this->_layout = layout;
	//this->_player_num = player_num;
}

Viewport ViewportManager::get_player_viewport(int player_num) const
{
    return this->calculate_viewport(
        this->_layout, player_num, this->_resolution_manager->get_resolution_vec());
}

std::vector<Viewport> ViewportManager::get_all_viewports() const
{
	std::vector<Viewport> result;
    int player_count = this->get_player_count_from_layout(this->_layout);
	for (int i = 0; i < player_count; i++)
	{
		result.push_back(this->get_player_viewport(i));
	}
    // Add a 4th viewport if there are 3 players
    if (player_count == 3)
    {
		result.push_back(this->get_player_viewport(4));
    }
	return result;
}

int ViewportManager::get_player_count_from_layout(screen_layout layout) const
{
	switch (layout)
	{
	case screen_layout::ONE_PLAYER:
		return 1;
	case screen_layout::TWO_PLAYER:
		return 2;
	case screen_layout::THREE_PLAYER:
		return 3;
	case screen_layout::FOUR_PLAYER:
		return 4;
	default:
		return 1;
	}
}

std::vector<MattMath::RectangleF> ViewportManager::get_viewport_dividers() const
{
    std::vector<RectangleF> result = std::vector<RectangleF>();
    const Vector2F res = this->_resolution_manager->get_resolution_vec();
    screen_layout layout = this->_layout;

    if (layout == screen_layout::ONE_PLAYER)
    {
		return result;
	}
    else if (layout == screen_layout::TWO_PLAYER)
    {
		result.push_back(RectangleF(0.0f, res.y / 2.0f - DIVIDER_THICKNESS / 2.0f,
            			res.x, DIVIDER_THICKNESS));
		return result;
	}
    else if (layout == screen_layout::THREE_PLAYER ||
        layout == screen_layout::FOUR_PLAYER)
    {
		result.push_back(RectangleF(0.0f, res.y / 2.0f - DIVIDER_THICKNESS / 2.0f,
            			res.x, DIVIDER_THICKNESS));
		result.push_back(RectangleF(res.x / 2.0f - DIVIDER_THICKNESS / 2.0f, 0.0f,
            			DIVIDER_THICKNESS, res.y));
		return result;
	}
    else
    {
		throw std::exception("Invalid screen layout");
    }
}

//std::vector<RectangleF> ViewportManager::get_viewport_dividers(int player_num) const
//{
//    std::vector<RectangleF> result = std::vector<RectangleF>();
//    //int player_count = this->get_player_count_from_layout(this->_layout);
//    Vector2F res = this->_resolution_manager->get_resolution_vec();
//    screen_layout layout = this->_layout;
//    switch (layout)
//    {
//    case screen_layout::ONE_PLAYER:
//		return result;
//    case screen_layout::TWO_PLAYER:
//        switch (player_num)
//        {
//        case 0:
//        {
//            Viewport vp = this->get_player_viewport(0);
//            result.push_back(RectangleF(0.0f, vp.height - DIVIDER_THICKNESS,
//                vp.width, DIVIDER_THICKNESS));
//            return result;
//        }
//        case 1:
//        {
//            Viewport vp = this->get_player_viewport(1);
//            result.push_back(RectangleF(0.0f, 0.0f, vp.width, DIVIDER_THICKNESS));
//            return result;
//        }
//        default:
//            throw std::exception("Invalid player number");
//        }
//    case screen_layout::THREE_PLAYER:
//        switch (player_num)
//        {
//        case 0:
//        {
//            Viewport vp = this->get_player_viewport(0);
//            result.push_back(RectangleF(0.0f, vp.height - DIVIDER_THICKNESS,
//                vp.width, DIVIDER_THICKNESS));
//            result.push_back(RectangleF(vp.width - DIVIDER_THICKNESS, 0.0f,
//                DIVIDER_THICKNESS, vp.height));
//            return result;
//        }
//        case 1:
//        {
//            Viewport vp = this->get_player_viewport(1);
//            result.push_back(RectangleF(0.0f, vp.height - DIVIDER_THICKNESS, vp.width,
//                DIVIDER_THICKNESS));
//            result.push_back(RectangleF(0.0f, 0.0f, DIVIDER_THICKNESS, vp.height));
//            return result;
//        }
//        case 2:
//        {
//            Viewport vp = this->get_player_viewport(2);
//            result.push_back(RectangleF(0.0f, 0.0f, vp.width, DIVIDER_THICKNESS));
//            result.push_back(RectangleF(vp.width - DIVIDER_THICKNESS, 0.0f,
//                DIVIDER_THICKNESS, vp.height));
//            return result;
//        }
//        default:
//            throw std::exception("Invalid player number");
//        }
//    case screen_layout::FOUR_PLAYER:
//        throw std::exception("4 player layout not implemented");
//    default:
//        throw std::exception("Invalid screen layout");
//    }
//}

Viewport ViewportManager::calculate_viewport(screen_layout layout,
	int player_num, const Vector2F& screen_size) const
{
    Viewport result = Viewport();
    switch (layout)
    {
    case screen_layout::ONE_PLAYER:
        result.x = 0.0f;
        result.y = 0.0f;
        result.width = screen_size.x;
        result.height = screen_size.y;
        return result;
    case screen_layout::TWO_PLAYER:
        switch (player_num)
        {
        case 0:
            result.x = 0.0f;
            result.y = 0.0f;
            result.width = screen_size.x;
            result.height = screen_size.y / 2.0f;
            return result;
        case 1:
            result.x = 0.0f;
            result.y = screen_size.y / 2.0f;
            result.width = screen_size.x;
            result.height = screen_size.y / 2.0f;
            return result;
        }
    case screen_layout::THREE_PLAYER:
        switch (player_num)
        {
        case 0:
            result.x = 0.0f;
            result.y = 0.0f;
            result.width = screen_size.x / 2.0f;
            result.height = screen_size.y / 2.0f;
            return result;
        case 1:
            result.x = screen_size.x / 2.0f;
            result.y = screen_size.y / 2.0f;
            result.width = screen_size.x / 2.0f;
            result.height = screen_size.y / 2.0f;
            return result;
        case 2:
            result.x = 0.0f;
            result.y = screen_size.y / 2.0f;
            result.width = screen_size.x / 2.0f;
            result.height = screen_size.y / 2.0f;
            return result;
        }
    case screen_layout::FOUR_PLAYER:
        switch (player_num)
        {
        case 0:
            result.x = 0.0f;
            result.y = 0.0f;
            result.width = screen_size.x / 2.0f;
            result.height = screen_size.y / 2.0f;
            return result;
        case 1:
            result.x = screen_size.x / 2.0f;
            result.y = 0.0f;
            result.width = screen_size.x / 2.0f;
            result.height = screen_size.y / 2.0f;
            return result;
        case 2:
            result.x = 0.0f;
            result.y = screen_size.y / 2.0f;
            result.width = screen_size.x / 2.0f;
            result.height = screen_size.y / 2.0f;
            return result;
        case 3:
            result.x = screen_size.x / 2.0f;
            result.y = screen_size.y / 2.0f;
            result.width = screen_size.x / 2.0f;
            result.height = screen_size.y / 2.0f;
            return result;
        }
    default: //1P screen
        result.x = 0.0f;
        result.y = 0.0f;
        result.width = screen_size.x;
        result.height = screen_size.y;
        return result;
    }
    
    //Viewport result = Viewport();
    //switch (layout)
    //{
    //case screen_layout::ONE_PLAYER:
    //    result.x = 0.0f;
    //    result.y = 0.0f;
    //    result.width = screen_size.x;
    //    result.height = screen_size.y;
    //    return result;
    //case screen_layout::TWO_PLAYER:
    //    switch (player_num)
    //    {
    //    case 0:
    //        result.x = 0.0f;
    //        result.y = screen_size.y / 2.0f + 1.0f;
    //        result.width = screen_size.x;
    //        result.height = screen_size.y / 2.0f - 1.0f;
    //        return result;

    //    case 1:
    //        result.x = 0.0f;
    //        result.y = 0.0f;
    //        result.width = screen_size.x;
    //        result.height = screen_size.y / 2.0f - 1.0f;
    //        return result;
    //    }
    //case screen_layout::THREE_PLAYER:
    //    switch (player_num)
    //    {
    //    case 0:
    //        result.x = 0.0f;
    //        result.y = screen_size.y / 2.0f + 1.0f;
    //        result.width = screen_size.x / 2.0f - 1.0f;
    //        result.height = screen_size.y / 2.0f - 1.0f;
    //        return result;

    //    case 1:
    //        result.x = screen_size.x / 2.0f + 1.0f;
    //        result.y = screen_size.y / 2.0f + 1.0f;
    //        result.width = screen_size.x / 2.0f - 1.0f;
    //        result.height = screen_size.y / 2.0f - 1.0f;
    //        return result;
    //    case 2:
    //        result.x = 0.0f;
    //        result.y = 0.0f;
    //        result.width = screen_size.x / 2.0f - 1.0f;
    //        result.height = screen_size.y / 2.0f - 1.0f;
    //        return result;
    //    }
    //case screen_layout::FOUR_PLAYER:
    //    switch (player_num)
    //    {
    //    case 0:
    //        result.x = 0.0f;
    //        result.y = screen_size.y / 2.0f + 1.0f;
    //        result.width = screen_size.x / 2.0f - 1.0f;
    //        result.height = screen_size.y / 2.0f - 1.0f;
    //        return result;

    //    case 1:
    //        result.x = screen_size.x / 2.0f + 1.0f;
    //        result.y = screen_size.y / 2.0f + 1.0f;
    //        result.width = screen_size.x / 2.0f - 1.0f;
    //        result.height = screen_size.y / 2.0f - 1.0f;
    //        return result;
    //    case 2:
    //        result.x = 0.0f;
    //        result.y = 0.0f;
    //        result.width = screen_size.x / 2.0f - 1.0f;
    //        result.height = screen_size.y / 2.0f - 1.0f;
    //        return result;
    //    case 3:
    //        result.x = screen_size.x / 2.0f + 1.0f;
    //        result.y = 0.0f;
    //        result.width = screen_size.x / 2.0f - 1.0f;
    //        result.height = screen_size.y / 2.0f - 1.0f;
    //        return result;
    //    }
    //default: //1P screen
    //    result.x = 0.0f;
    //    result.y = 0.0f;
    //    result.width = screen_size.x;
    //    result.height = screen_size.y;
    //    return result;
    //}
}