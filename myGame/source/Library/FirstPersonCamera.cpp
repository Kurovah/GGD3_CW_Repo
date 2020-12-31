#include "FirstPersonCamera.h"
#include "Game.h"
#include "GameTime.h"
#include "Keyboard.h"
#include "Mouse.h"
#include "VectorHelper.h"

namespace Library
{
    RTTI_DEFINITIONS(FirstPersonCamera)

    const float FirstPersonCamera::DefaultRotationRate = XMConvertToRadians(1.0f);
    const float FirstPersonCamera::DefaultMovementRate = 00.0f;
    const float FirstPersonCamera::DefaultMouseSensitivity = 100.0f;

    FirstPersonCamera::FirstPersonCamera(Game& game)
        : Camera(game), mKeyboard(nullptr), mMouse(nullptr), 
          mMouseSensitivity(DefaultMouseSensitivity), mRotationRate(DefaultRotationRate), mMovementRate(DefaultMovementRate),
		moveSpeed(XMLoadFloat3(&Vector3Helper::Zero)),actualMoveSpeed(XMLoadFloat3(&Vector3Helper::Zero)), targetMoveSpeed(XMLoadFloat3(&Vector3Helper::Zero)), blendFloat(0.0f)
    {
		hasZeroed = false;
    }

    FirstPersonCamera::FirstPersonCamera(Game& game, float fieldOfView, float aspectRatio, float nearPlaneDistance, float farPlaneDistance)
        : Camera(game, fieldOfView, aspectRatio, nearPlaneDistance, farPlaneDistance), mKeyboard(nullptr), mMouse(nullptr),
          mMouseSensitivity(DefaultMouseSensitivity), mRotationRate(DefaultRotationRate), mMovementRate(DefaultMovementRate),
		moveSpeed(XMLoadFloat3(&Vector3Helper::Zero)), actualMoveSpeed(XMLoadFloat3(&Vector3Helper::Zero)), targetMoveSpeed(XMLoadFloat3(&Vector3Helper::Zero)),blendFloat(0.0f)
          
    {
		hasZeroed = false;
    }

    FirstPersonCamera::~FirstPersonCamera()
    {
        mKeyboard = nullptr;
        mMouse = nullptr;
    }

    const Keyboard& FirstPersonCamera::GetKeyboard() const
    {
        return *mKeyboard;
    }

    void FirstPersonCamera::SetKeyboard(Keyboard& keyboard)
    {
        mKeyboard = &keyboard;
    }

    const Mouse& FirstPersonCamera::GetMouse() const
    {
        return *mMouse;
    }

    void FirstPersonCamera::SetMouse(Mouse& mouse)
    {
        mMouse = &mouse;
    }

    float&FirstPersonCamera:: MouseSensitivity()
    {
        return mMouseSensitivity;
    }


    float& FirstPersonCamera::RotationRate()
    {
        return mRotationRate;
    }

    float& FirstPersonCamera::MovementRate()
    {
        return mMovementRate;
    }

    void FirstPersonCamera::Initialize()
    {
        mKeyboard = (Keyboard*)mGame->Services().GetService(Keyboard::TypeIdClass());
        mMouse = (Mouse*)mGame->Services().GetService(Mouse::TypeIdClass());

        Camera::Initialize();
    }

    void FirstPersonCamera::Update(const GameTime& gameTime)
    {
		/*
		XMFLOAT3 movementAmount = Vector3Helper::Zero;
        if (mKeyboard != nullptr)
        {
            if (mKeyboard->IsKeyDown(DIK_W))
            {
                movementAmount.z = 1.0f;
            }

            if (mKeyboard->IsKeyDown(DIK_S))
            {
                movementAmount.z = -1.0f;
            }

            if (mKeyboard->IsKeyDown(DIK_A))
            {
                movementAmount.x = -1.0f;
            }

            if (mKeyboard->IsKeyDown(DIK_D))
            {
                movementAmount.x = 1.0f;
            }

			//up and down move
			if (mKeyboard->IsKeyDown(DIK_Q)) {
				movementAmount.y = 1.0f;
			}
			if (mKeyboard->IsKeyDown(DIK_E)) {
				movementAmount.y = -1.0f;
			}
        }

        XMFLOAT2 rotationAmount = Vector2Helper::Zero;
        if ((mMouse != nullptr) && (mMouse->IsButtonHeldDown(MouseButtonsLeft)))
        {
            LPDIMOUSESTATE mouseState = mMouse->CurrentState();			
            rotationAmount.x = -mouseState->lX * mMouseSensitivity;
            rotationAmount.y = -mouseState->lY * mMouseSensitivity;
        }

		float elapsedTime = (float)gameTime.ElapsedGameTime();
        XMVECTOR rotationVector = XMLoadFloat2(&rotationAmount) * mRotationRate * elapsedTime;
        XMVECTOR right = XMLoadFloat3(&mRight);

        XMMATRIX pitchMatrix = XMMatrixRotationAxis(right, XMVectorGetY(rotationVector));
        XMMATRIX yawMatrix = XMMatrixRotationY(XMVectorGetX(rotationVector));

        ApplyRotation(XMMatrixMultiply(pitchMatrix, yawMatrix));

        XMVECTOR position = XMLoadFloat3(&mPosition);
		XMVECTOR movement = XMLoadFloat3(&movementAmount) * mMovementRate * elapsedTime;

		//refresh movespeed
		moveSpeed = XMLoadFloat3(&Vector3Helper::Zero);
		XMVECTOR strafe = right * XMVectorGetX(movement);
        moveSpeed += strafe;

        XMVECTOR forward = XMLoadFloat3(&mDirection) * XMVectorGetZ(movement);
		moveSpeed += forward;

		XMVECTOR rise = XMLoadFloat3(&mUp) * XMVectorGetY(movement);
		moveSpeed += rise;
        
		actualMoveSpeed = XMVectorLerp(actualMoveSpeed, moveSpeed, elapsedTime);
		
		
		position += actualMoveSpeed;
		//this updates the position
        XMStoreFloat3(&mPosition, position);
		*/
        Camera::Update(gameTime);
    }
}
