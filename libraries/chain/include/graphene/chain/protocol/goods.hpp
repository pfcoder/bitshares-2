/*
 * Copyright (c) 2016 OKey, Inc., and contributors.
 *
 * The MIT License
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */
#pragma once
#include <graphene/chain/protocol/base.hpp>
#include <graphene/chain/protocol/config.hpp>
#include <graphene/chain/protocol/types.hpp>

namespace graphene { namespace chain {
   /**
    * @brief Goods means a single product generation
    *
    * Every goods has a unique token(public key) to identify it, goods could 
    * delivered between accounts, it can be treated as ownership transfer, 
    * the goods also could be owned by multiple accounts (share mode)
    */
   struct goods
   {
      goods( product_id_type product_id, goods_id_type goods_id = goods_id_type() )
      :id(goods_id){}

      goods_id_type id;
      product_id_type product_id;

      void validate() const;

   };

   /**
    * @ingroup operations
    */
   struct goods_create_operation : public base_operation
   {
      struct fee_parameters_type
      {
         uint64_t basic_fee       = 5*GRAPHENE_BLOCKCHAIN_PRECISION;
         uint32_t price_per_kbyte = GRAPHENE_BLOCKCHAIN_PRECISION;
      };

      asset           fee;
      /// This account must sign and pay the fee for this operation. Later, this account may update the goods
      account_id_type         issuer;

      account_id_type fee_payer()const { return issuer; }
      void            validate()const;
      share_type      calculate_fee(const fee_parameters_type& )const;
   };

   struct goods_deliver_operation : public base_operation
   {
      struct fee_parameters_type
      {
         uint64_t basic_fee       = 5*GRAPHENE_BLOCKCHAIN_PRECISION;
         uint32_t price_per_kbyte = GRAPHENE_BLOCKCHAIN_PRECISION;
      };

      asset           fee;

      account_id_type         from;
      account_id_type         to;

      account_id_type fee_payer()const { return from; }
      void            validate()const;
      share_type      calculate_fee(const fee_parameters_type& )const;
   };
} }

FC_REFLECT( graphene::chain::goods, (product_id)(id) )
FC_REFLECT( graphene::chain::goods_create_operation::fee_parameters_type, (basic_fee)(price_per_kbyte) )
FC_REFLECT( graphene::chain::goods_deliver_operation::fee_parameters_type, (basic_fee)(price_per_kbyte) )
FC_REFLECT( graphene::chain::goods_create_operation,
            (fee)
            (issuer)
          )
FC_REFLECT( graphene::chain::goods_deliver_operation,
            (fee)
            (from)
            (to)
          )