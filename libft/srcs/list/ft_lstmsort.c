/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmsort.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsudo <tsudo@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/01 00:00:00 by tsudo             #+#    #+#             */
/*   Updated: 2022/08/01 00:00:00 by tsudo            ###   ##########        */
/*                                                                            */
/* ************************************************************************** */

#include "ft_list.h"

/* ************************************************************************** */
/*  This helper function divides a list into two,                             */
/*  and returns the orifinal size.                                            */
/*  The latter list starts at index of (size + 1) / 2.                        */
/*  Next member of list preceeding the latter one will be NULL.               */
/* ************************************************************************** */
static size_t	lms_divide(t_list *head, t_list **mid_ptr)
{
	t_list	*mid;
	size_t	size;
	size_t	mid_idx;
	size_t	i;

	size = ft_lstsize(head);
	if (size < 2)
	{
		*mid_ptr = NULL;
		return (size);
	}
	mid = head;
	mid_idx = (size + 1) / 2;
	i = 0;
	while (i < mid_idx - 1)
	{
		mid = mid->next;
		i++;
	}
	*mid_ptr = mid->next;
	mid->next = NULL;
	return (size);
}

/* ************************************************************************** */
/*  This helper function merges two sorted lists, using cmp function.         */
/* ************************************************************************** */
static t_list	*lms_merge(\
	t_list *head, t_list *mid, int (*cmp)(void *, void *))
{
	t_list	*sorted;
	t_list	*next;

	sorted = NULL;
	while (head != NULL && mid != NULL)
	{
		if (cmp(head->content, mid->content) > 0)
		{
			next = mid->next;
			mid->next = NULL;
			ft_lstadd_back(&sorted, mid);
			mid = next;
		}
		else
		{
			next = head->next;
			head->next = NULL;
			ft_lstadd_back(&sorted, head);
			head = next;
		}
	}
	ft_lstadd_back(&sorted, head);
	ft_lstadd_back(&sorted, mid);
	return (sorted);
}

/* ************************************************************************** */
/*  This helper function merge-sorts the list using cmp function.             */
/* ************************************************************************** */
static t_list	*lms_helper(t_list *lst, int (*cmp)(void *, void *))
{
	t_list	*mid;
	size_t	size;

	size = lms_divide(lst, &mid);
	if (size < 2)
		return (lst);
	if (size == 2)
	{
		if (cmp(lst->content, mid->content) <= 0)
			ft_lstadd_back(&lst, mid);
		else
			ft_lstadd_front(&lst, mid);
		return (lst);
	}
	lst = lms_helper(lst, cmp);
	mid = lms_helper(mid, cmp);
	return (lms_merge(lst, mid, cmp));
}

/* ************************************************************************** */
/*  This function merge-sorts the list using cmp function.                    */
/*  When sorting in ascending order, cmp(big, small) should return positive.  */
/* ************************************************************************** */
void	ft_lstmsort(t_list **lst, int (*cmp)(void *, void *))
{
	*lst = lms_helper(*lst, cmp);
}
