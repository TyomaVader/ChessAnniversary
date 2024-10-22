// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "ChessEngine/AI.h"

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ChessEngine.generated.h"

UCLASS(Blueprintable)
class CHESSDEV_API AChessEngine : public AActor
{
	GENERATED_BODY()

// Methods
public:	
	// Sets default values for this actor's properties
	AChessEngine();

	/**
	 * @brief Sets board position from a FEN string.
	 * 
	 * @param shortFen The FEN string.
	 * @param enPassant The en passant ability.
	 * @param whiteLongCastling The white long castling ability.
	 * @param whiteShortCastling The white short castling ability.
	 * @param blackLongCastling The black long castling ability.
	 * @param blackShortCastling The black short castling ability.
	 * @param moveCtr The move counter.
	 * 
	 * @return void
	*/
	UFUNCTION(BlueprintCallable, Category = "ChessEngine")
	void setBoardPosition(const FString& shortFen, uint8 enPassant, bool whiteLongCastling, bool whiteShortCastling, bool blackLongCastling, bool blackShortCastling, float moveCtr);

	/**
	 * @brief Checks if the game is finished.
	 * 
	 * @return 1 if white won, 2 if black won, 3 if it's a draw, 0 if game isn't finished yet.
	*/
	UFUNCTION(BlueprintCallable, Category = "ChessEngine")
	int isGameFinished() const;

	/**
	 * @brief Checks if the move is legal and makes it if it is.
	 * 
	 * @param from The square from which the piece is moved.
	 * @param to The square to which the piece is moved.
	 * @param side The side that makes the move. (0 - white, 1 - black)
	 * 
	 * @retval True The move is legal and was made.
	 * @retval False The move is illegal.
	*/
	UFUNCTION(BlueprintCallable, Category = "ChessEngine")
	bool makeMove(FIntPoint from, FIntPoint to, uint8 side, uint8 promotionPiece);

	/**
	 * @brief AI chooses the best move and makes it.
	 * 
	 * @param from Variable to which the chosen move starting square is assigned.
	 * @param to Variable to which the chosen move ending square is assigned.
	 * @param promotionPiece Variable to which the chosen promotion piece is assigned, if the move is a promotion.
	 * 
	 * @return void
	*/
	UFUNCTION(BlueprintCallable, Category = "ChessEngine")
	void makeAIMove(FIntPoint& from, FIntPoint& to, uint8& promotionPiece);

	UFUNCTION(BlueprintCallable, Category = "ChessEngine")
	bool makeCCGMove(FIntPoint from, FIntPoint to, uint8 side, uint8 promotionPiece, uint8 pieceToSpawn);

protected:
	bool whiteVictory() const;

	bool blackVictory() const;

	bool draw() const;

	bool isWhiteMove() const;

	bool isBlackMove() const;

// Events
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

// Properties
protected:
	/**
	 * @brief The board position.
	*/
	BoardPosition boardPosition;

	AI ai = { "/OpeningBook.txt" };

	MoveList moves;

	ChessMove move;

	uint8_t playerSide;
	uint8_t opponentSide;

	ChessMove playerMove;
};
